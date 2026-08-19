//! Interactive terminal UI, shown when the CLI is run with no subcommand.
//!
//! Every control maps to one parameter in [`crate::transport::id`].
//!
//! Writes happen on change, not on exit: moving a slider sends immediately,
//! which is what makes the UI usable for A/B listening.

use std::io;
use std::time::Duration;

use crossterm::event::{self, Event, KeyCode, KeyEvent, KeyEventKind, KeyModifiers};
use crossterm::terminal::{
    EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode, enable_raw_mode,
};
use crossterm::{ExecutableCommand, event::DisableMouseCapture, event::EnableMouseCapture};
use ratatui::Terminal;
use ratatui::backend::CrosstermBackend;
use ratatui::layout::{Constraint, Direction, Layout, Rect};
use ratatui::style::{Color, Modifier, Style};
use ratatui::text::{Line, Span};
use ratatui::widgets::{Block, Borders, Paragraph};
use tui_slider::{Slider, SliderOrientation, SliderState};

use crate::proto::{
    Crystalizer, DialogPlus, Feature, GraphicEq, SimpleSurround, SmartVolume, SmartVolumeMode,
    XBass,
};
use crate::{Result, SoundBlasterE5};

/// What a row writes when it changes.
///
/// Each variant carries both halves of a control, because every row draws its
/// on/off switch and its value on the same line -- an effect is one thing to
/// the user, not two.
#[derive(Clone, Copy, PartialEq, Eq)]
enum Control {
    /// An effect: an enable switch plus a normalized `0.0..=1.0` level.
    Effect {
        feature: Feature,
        enable: u32,
        level: u32,
    },
    /// The SBX master switch. Behaves as an on/off switch everywhere the UI
    /// is concerned, but has no `0x20` selector: it rides its own `0x23`
    /// opcode -- see [`SoundBlasterE5::set_sbx_master`].
    SbxMaster,
    /// The Smart Volume profile: an enumerated choice, not a level. Left/
    /// right step through [`SmartVolumeMode::ALL`]; it has no switch of its
    /// own, riding the Smart Volume row's enable instead.
    SmartVolumeMode,
    /// The graphic EQ: an enable switch plus ten band gains. Drawn as the
    /// panel below the row list rather than as a line in it, so selecting
    /// this row highlights the panel. Left/right move a cursor between
    /// bands; `+`/`-` change the band under the cursor.
    Eq,
}

/// Center frequency label for each of the ten EQ bands.
const EQ_FREQS: [&str; 10] = [
    "31Hz", "62Hz", "125Hz", "250Hz", "500Hz", "1kHz", "2kHz", "4kHz", "8kHz", "16kHz",
];

/// Full-scale EQ band gain, in dB. Bars are drawn against +/- this, and
/// it is also how far a band can be dragged here.
///
/// Tied to the library bound so the UI cannot render a band the CLI is
/// allowed to set.
const EQ_SCALE_DB: f32 = crate::EQ_GAIN_DB.1;

struct Row {
    label: &'static str,
    control: Control,
    /// The row's on/off switch.
    on: bool,
    /// Normalized level, `0.0..=1.0`. Unused outside `Control::Effect`.
    value: f32,
    /// The ten band gains, in dB. Unused outside `Control::Eq`.
    bands: [f32; 10],
    /// Which band left/right moves, when `control` is `Control::Eq`.
    band_cursor: usize,
    /// The selected profile. Unused outside `Control::SmartVolumeMode`.
    mode: SmartVolumeMode,
}

impl Row {
    /// True for a row with a level to slide, as opposed to a bare switch.
    fn has_level(&self) -> bool {
        matches!(self.control, Control::Effect { .. })
    }

    /// True for a row that has no on/off switch of its own, so the switch
    /// column is left blank rather than drawn permanently off.
    fn has_switch(&self) -> bool {
        !matches!(self.control, Control::SmartVolumeMode)
    }

    /// Step size for one arrow-key press on the row's level.
    fn step(&self) -> f32 {
        0.05
    }

    /// The value shown in the right-hand column.
    fn display(&self) -> String {
        match self.control {
            Control::Effect { .. } => format!("{:.0}%", self.value * 100.0),
            Control::SmartVolumeMode => self.mode.to_string(),
            Control::SbxMaster | Control::Eq => if self.on { "on" } else { "off" }.into(),
        }
    }
}

/// Build a row with the EQ-only fields defaulted; only `rows()` needs those.
fn row(label: &'static str, control: Control, on: bool, value: f32) -> Row {
    Row {
        label,
        control,
        on,
        value,
        bands: [0.0; 10],
        band_cursor: 0,
        mode: SmartVolumeMode::Normal,
    }
}

/// The rows the UI shows, in display order.
///
/// The EQ row is last because it is drawn as the panel underneath the list.
fn rows() -> Vec<Row> {
    /// One effect: its enable switch and its level, on a single row.
    fn effect(label: &'static str, feature: Feature, enable: u32, level: u32, default: f32) -> Row {
        row(
            label,
            Control::Effect {
                feature,
                enable,
                level,
            },
            true,
            default,
        )
    }

    // Replaced by the real state on startup; see `App::refresh_from_device`.
    vec![
        row("SBX master", Control::SbxMaster, false, 0.0),
        effect(
            "Surround",
            Feature::EffectsSimpleSurround,
            SimpleSurround::Enable as u32,
            SimpleSurround::Level as u32,
            0.12,
        ),
        effect(
            "Crystalizer",
            Feature::EffectsCrystalizer,
            Crystalizer::Enable as u32,
            Crystalizer::Level as u32,
            0.5,
        ),
        effect(
            "Bass",
            Feature::EffectsXBass,
            XBass::Enable as u32,
            XBass::Strength as u32,
            0.3,
        ),
        effect(
            "Dialog Plus",
            Feature::EffectsDialogPlus,
            DialogPlus::Enable as u32,
            DialogPlus::Strength as u32,
            0.5,
        ),
        effect(
            "Smart Volume",
            Feature::EffectsSmartVolume,
            SmartVolume::Enable as u32,
            SmartVolume::Strength as u32,
            0.74,
        ),
        row("  profile", Control::SmartVolumeMode, false, 0.0),
        row("Graphic EQ", Control::Eq, false, 0.0),
    ]
}

/// UI state.
struct App {
    rows: Vec<Row>,
    selected: usize,
    /// Last write's outcome, shown in the status bar.
    status: String,
    dry_run: bool,
}

impl App {
    fn new(dry_run: bool) -> Self {
        Self {
            rows: rows(),
            selected: 0,
            status: "arrows adjust, space toggles, q quits".into(),
            dry_run,
        }
    }

    /// Record the outcome of a write in the status bar.
    fn report(&mut self, result: Result<()>, what: String) {
        let label = self.rows[self.selected].label;
        self.status = match result {
            Ok(()) => what,
            Err(e) => format!("{label}: {e}"),
        };
    }

    /// Send the selected row's level. A no-op on rows that have none.
    fn write_level(&mut self, dev: &mut SoundBlasterE5) {
        let row = &self.rows[self.selected];
        let Control::Effect {
            feature,
            level: param,
            ..
        } = row.control
        else {
            return;
        };
        let result = dev.set_level_raw(feature, param, row.value);
        let what = format!("{} = {}", row.label, row.display());
        self.report(result, what);
    }

    /// Send the selected row's on/off switch, whichever opcode it rides.
    fn write_switch(&mut self, dev: &mut SoundBlasterE5) {
        let row = &self.rows[self.selected];
        let on = row.on;
        let result = match row.control {
            Control::Effect {
                feature,
                enable: param,
                ..
            } => dev.set_enable_raw(feature, param, on),
            Control::Eq => {
                dev.set_enable_raw(Feature::EffectsGraphicEQ, GraphicEq::Enable as u32, on)
            }
            // A profile is a choice, not a switch: toggling it would have
            // nothing to write.
            Control::SmartVolumeMode => return,
            // The master switch has no `0x20` selector -- it rides its own
            // `0x23 0x23` opcode, and answers with the state it ended up in.
            Control::SbxMaster => {
                let got = dev.set_sbx_master(on);
                if let Ok(reported) = got {
                    self.rows[self.selected].on = reported;
                }
                got.map(|_| ())
            }
        };

        let row = &self.rows[self.selected];
        let what = format!("{} {}", row.label, if row.on { "on" } else { "off" });
        self.report(result, what);
    }

    /// Send the EQ band under the cursor.
    fn write_band(&mut self, dev: &mut SoundBlasterE5) {
        let row = &self.rows[self.selected];
        let band = row.band_cursor;
        let db = row.bands[band];
        let result = dev.set_eq_band(band as u8, db);
        let what = format!("EQ {} {db:+.1}dB", EQ_FREQS[band]);
        self.report(result, what);
    }

    /// Left/right adjusts the selected row's level; on the EQ row it moves
    /// which band `+`/`-` will change.
    fn adjust(&mut self, dir: f32, dev: &mut SoundBlasterE5) {
        match self.rows[self.selected].control {
            // A switch has nothing to slide; left/right just flips it.
            Control::SbxMaster => self.toggle(dev),
            Control::Eq => self.move_band_cursor(dir),
            Control::SmartVolumeMode => self.cycle_mode(dir, dev),
            Control::Effect { .. } => {
                let row = &mut self.rows[self.selected];
                let step = row.step();
                row.value = (row.value + dir * step).clamp(0.0, 1.0);
                // Kill float drift so 0.05 steps land on clean values.
                row.value = (row.value / step).round() * step;
                self.write_level(dev);
            }
        }
    }

    /// Step to the next or previous profile and send it. Clamps at the
    /// ends rather than wrapping, so holding an arrow settles instead of
    /// cycling past the choice the user wanted.
    fn cycle_mode(&mut self, dir: f32, dev: &mut SoundBlasterE5) {
        let row = &mut self.rows[self.selected];
        let last = SmartVolumeMode::ALL.len() as isize - 1;
        let i = SmartVolumeMode::ALL
            .iter()
            .position(|m| *m == row.mode)
            .unwrap_or(0) as isize;
        let next = (i + dir.signum() as isize).clamp(0, last) as usize;
        if SmartVolumeMode::ALL[next] == row.mode {
            return;
        }
        row.mode = SmartVolumeMode::ALL[next];
        let mode = row.mode;
        let label = row.label;
        let result = dev.set_smart_volume_mode(mode);
        self.report(result, format!("{} = {mode}", label.trim()));
    }

    fn move_band_cursor(&mut self, dir: f32) {
        let row = &mut self.rows[self.selected];
        let cursor = row.band_cursor as isize + dir.signum() as isize;
        row.band_cursor = cursor.clamp(0, 9) as usize;
    }

    /// Raise or lower the EQ band under the cursor. Only meaningful on the
    /// EQ row; a no-op elsewhere.
    fn adjust_band(&mut self, dir: f32, dev: &mut SoundBlasterE5) {
        if !matches!(self.rows[self.selected].control, Control::Eq) {
            return;
        }
        const STEP: f32 = 0.5;
        let row = &mut self.rows[self.selected];
        let v = &mut row.bands[row.band_cursor];
        *v = (*v + dir * STEP).clamp(-EQ_SCALE_DB, EQ_SCALE_DB);
        *v = (*v / STEP).round() * STEP;
        self.write_band(dev);
    }

    fn toggle(&mut self, dev: &mut SoundBlasterE5) {
        self.rows[self.selected].on = !self.rows[self.selected].on;
        self.write_switch(dev);
    }

    /// Pull each row's live value from the device, replacing the built-in
    /// defaults in [`rows`]. Best-effort: a row whose read fails -- dry-run
    /// or no device -- keeps its default and is left alone.
    fn refresh_from_device(&mut self, dev: &mut SoundBlasterE5) {
        if dev.is_dry_run() {
            self.status = "dry run: showing defaults, not device state".into();
            return;
        }

        let mut read_ok = 0usize;
        let mut read_err = 0usize;
        /// Store a read that succeeded, count either way.
        fn tally(slot: &mut f32, got: Result<f32>, ok: &mut usize, err: &mut usize) {
            match got {
                Ok(v) => {
                    *slot = v;
                    *ok += 1;
                }
                Err(_) => *err += 1,
            }
        }

        for row in &mut self.rows {
            match row.control {
                Control::Effect {
                    feature,
                    enable,
                    level,
                } => {
                    let mut flag = f32::from(u8::from(row.on));
                    tally(
                        &mut flag,
                        dev.get_level_raw(feature, enable),
                        &mut read_ok,
                        &mut read_err,
                    );
                    row.on = flag >= 0.5;
                    tally(
                        &mut row.value,
                        dev.get_level_raw(feature, level),
                        &mut read_ok,
                        &mut read_err,
                    );
                }
                Control::SmartVolumeMode => match dev.get_smart_volume_mode() {
                    Ok(mode) => {
                        row.mode = mode;
                        read_ok += 1;
                    }
                    Err(_) => read_err += 1,
                },
                Control::SbxMaster => match dev.get_sbx_master() {
                    Ok(on) => {
                        row.on = on;
                        read_ok += 1;
                    }
                    Err(_) => read_err += 1,
                },
                Control::Eq => {
                    let mut flag = f32::from(u8::from(row.on));
                    tally(
                        &mut flag,
                        dev.get_level_raw(Feature::EffectsGraphicEQ, GraphicEq::Enable as u32),
                        &mut read_ok,
                        &mut read_err,
                    );
                    row.on = flag >= 0.5;
                    for (band, gain) in row.bands.iter_mut().enumerate() {
                        let param = GraphicEq::Band0Gain as u32 + band as u32;
                        tally(
                            gain,
                            dev.get_level_raw(Feature::EffectsGraphicEQ, param),
                            &mut read_ok,
                            &mut read_err,
                        );
                    }
                }
            }
        }

        self.status = if read_err == 0 {
            format!("loaded {read_ok} values from device")
        } else {
            format!("loaded {read_ok} values from device, {read_err} unread (kept defaults)")
        };
    }
}

/// Puts the terminal into raw/alternate-screen mode, and restores it on the
/// way out.
///
/// This is a guard rather than a pair of calls around the event loop so the
/// restore also runs when the loop *panics*. Unwinding past a bare
/// `disable_raw_mode()` would otherwise drop the user back into a shell
/// with no echo and no cursor.
struct TerminalGuard;

impl TerminalGuard {
    fn enter() -> Result<Self> {
        enable_raw_mode()?;
        let mut out = io::stdout();
        out.execute(EnterAlternateScreen)?;
        out.execute(EnableMouseCapture)?;
        Ok(Self)
    }
}

impl Drop for TerminalGuard {
    fn drop(&mut self) {
        // Best-effort: this runs while unwinding, where returning an error
        // is not an option and panicking again would abort the process.
        let _ = disable_raw_mode();
        let mut out = io::stdout();
        let _ = out.execute(LeaveAlternateScreen);
        let _ = out.execute(DisableMouseCapture);
        let _ = out.execute(crossterm::cursor::Show);
    }
}

/// Run the interactive UI until the user quits.
pub fn run(dev: &mut SoundBlasterE5) -> Result<()> {
    let mut app = App::new(dev.is_dry_run());
    app.refresh_from_device(dev);

    let _guard = TerminalGuard::enter()?;
    let backend = CrosstermBackend::new(io::stdout());
    let mut terminal = Terminal::new(backend)?;

    event_loop(&mut terminal, &mut app, dev)
}

fn event_loop(
    terminal: &mut Terminal<CrosstermBackend<io::Stdout>>,
    app: &mut App,
    dev: &mut SoundBlasterE5,
) -> Result<()> {
    loop {
        terminal.draw(|f| draw(f, app))?;

        if !event::poll(Duration::from_millis(200))? {
            continue;
        }
        let Event::Key(KeyEvent {
            code,
            modifiers,
            kind,
            ..
        }) = event::read()?
        else {
            continue;
        };
        // Windows sends both press and release; only act on press.
        if kind != KeyEventKind::Press {
            continue;
        }

        match code {
            KeyCode::Char('q') | KeyCode::Esc => return Ok(()),
            KeyCode::Char('c') if modifiers.contains(KeyModifiers::CONTROL) => return Ok(()),
            KeyCode::Up | KeyCode::Char('k') => {
                app.selected = app.selected.saturating_sub(1);
            }
            KeyCode::Down | KeyCode::Char('j') => {
                app.selected = (app.selected + 1).min(app.rows.len() - 1);
            }
            KeyCode::Left | KeyCode::Char('h') => app.adjust(-1.0, dev),
            KeyCode::Right | KeyCode::Char('l') => app.adjust(1.0, dev),
            KeyCode::Char('+') | KeyCode::Char('=') => app.adjust_band(1.0, dev),
            KeyCode::Char('-') | KeyCode::Char('_') => app.adjust_band(-1.0, dev),
            KeyCode::Char(' ') | KeyCode::Enter => app.toggle(dev),
            _ => {}
        }
    }
}

fn draw(f: &mut ratatui::Frame, app: &App) {
    // The row list is short and fixed, so it takes exactly the height it
    // needs and the EQ panel absorbs whatever is left -- the EQ is the part
    // that reads better tall.
    let listed = app.rows.iter().filter(|r| !r.is_eq()).count() as u16;
    let list_h = (listed + 2).min(f.area().height.saturating_sub(4));

    let chunks = Layout::default()
        .direction(Direction::Vertical)
        .constraints([
            Constraint::Length(1),
            Constraint::Length(list_h),
            Constraint::Min(4),
            Constraint::Length(2),
        ])
        .split(f.area());

    let title = if app.dry_run {
        "Sound Blaster E5  --  DRY RUN, nothing is sent"
    } else {
        "Sound Blaster E5"
    };
    f.render_widget(
        Paragraph::new(title).style(
            Style::default()
                .fg(if app.dry_run {
                    Color::Yellow
                } else {
                    Color::Cyan
                })
                .add_modifier(Modifier::BOLD),
        ),
        chunks[0],
    );

    draw_rows(f, app, chunks[1]);
    draw_eq_panel(f, app, chunks[2]);

    let help = Line::from(vec![
        Span::styled("↑↓", Style::default().fg(Color::Cyan)),
        Span::raw(" select   "),
        Span::styled("←→", Style::default().fg(Color::Cyan)),
        Span::raw(" level / profile / pick band   "),
        Span::styled("+-", Style::default().fg(Color::Cyan)),
        Span::raw(" band gain   "),
        Span::styled("space", Style::default().fg(Color::Cyan)),
        Span::raw(" on/off   "),
        Span::styled("q", Style::default().fg(Color::Cyan)),
        Span::raw(" quit"),
    ]);
    let status = Paragraph::new(vec![Line::from(app.status.clone()), help]);
    f.render_widget(status, chunks[3]);
}

impl Row {
    fn is_eq(&self) -> bool {
        matches!(self.control, Control::Eq)
    }
}

/// A horizontal bar of `width` cells filled to `ratio`, drawn as text so it
/// has no reserved label cell to leave a gap in the middle.
///
/// The filled and unfilled halves are separate spans: the track has to stay
/// dim whatever colour the fill is, or it reads as part of the bar.
fn bar(ratio: f32, width: usize, colour: Color) -> Line<'static> {
    let filled = (ratio.clamp(0.0, 1.0) * width as f32).round() as usize;
    Line::from(vec![
        Span::styled("█".repeat(filled), Style::default().fg(colour)),
        Span::styled(
            "░".repeat(width - filled),
            Style::default().fg(Color::DarkGray),
        ),
    ])
}

/// Colours for a switch: green when on, dim when off.
fn switch_style(on: bool, selected: bool) -> (&'static str, Style) {
    let glyph = if on { "●" } else { "○" };
    let colour = match (on, selected) {
        (true, _) => Color::Green,
        (false, true) => Color::Gray,
        (false, false) => Color::DarkGray,
    };
    (glyph, Style::default().fg(colour))
}

fn draw_rows(f: &mut ratatui::Frame, app: &App, area: Rect) {
    let block = Block::default().borders(Borders::ALL);
    let inner = block.inner(area);
    f.render_widget(block, area);
    if inner.width < 20 || inner.height == 0 {
        return;
    }

    // Every label gets the same column, sized to the longest one, so the
    // switches and bars line up whatever the labels are.
    let label_w = app
        .rows
        .iter()
        .filter(|r| !r.is_eq())
        .map(|r| r.label.len())
        .max()
        .unwrap_or(12) as u16
        + 1;

    let listed: Vec<(usize, &Row)> = app
        .rows
        .iter()
        .enumerate()
        .filter(|(_, r)| !r.is_eq())
        .collect();

    // One line per row; scroll so the selection stays visible.
    let height = inner.height as usize;
    let sel_pos = listed.iter().position(|(i, _)| *i == app.selected);
    let first = sel_pos
        .unwrap_or(0)
        .saturating_sub(height.saturating_sub(1));

    for (i, (idx, row)) in listed.iter().skip(first).take(height).enumerate() {
        let y = inner.y + i as u16;
        let line = Rect::new(inner.x, y, inner.width, 1);
        let cols = Layout::default()
            .direction(Direction::Horizontal)
            .constraints([
                Constraint::Length(3),
                Constraint::Length(label_w),
                Constraint::Min(8),
                // Wide enough for the longest value, `normal`, plus the
                // gutter that keeps it off the border.
                Constraint::Length(8),
            ])
            .split(line);

        let selected = *idx == app.selected;

        if row.has_switch() {
            let (glyph, style) = switch_style(row.on, selected);
            f.render_widget(Paragraph::new(format!(" {glyph}")).style(style), cols[0]);
        }

        let label_style = if selected {
            Style::default().fg(Color::Black).bg(Color::Cyan)
        } else if row.on || !row.has_switch() {
            Style::default()
        } else {
            Style::default().fg(Color::DarkGray)
        };
        f.render_widget(Paragraph::new(row.label).style(label_style), cols[1]);

        if row.has_level() {
            // A disabled effect keeps its level on screen, dimmed, so it is
            // clear what it will go back to when switched on again.
            let colour = if row.on { Color::Blue } else { Color::DarkGray };
            f.render_widget(
                Paragraph::new(bar(row.value, cols[2].width as usize, colour)),
                cols[2],
            );
        }

        let value_style = if row.on || !row.has_switch() {
            Style::default()
        } else {
            Style::default().fg(Color::DarkGray)
        };
        f.render_widget(
            Paragraph::new(format!("{:>7}", row.display())).style(value_style),
            cols[3],
        );
    }
}

/// A 10-band equalizer: one vertical `tui-slider` per band (range
/// `-EQ_SCALE_DB..=EQ_SCALE_DB`, bottom-filled), with frequency labels
/// underneath. The
/// selected band shows its gain in place of its frequency.
fn draw_eq_panel(f: &mut ratatui::Frame, app: &App, area: Rect) {
    let Some(eq_row) = app.rows.iter().find(|r| r.is_eq()) else {
        return;
    };
    let selected = app.rows[app.selected].is_eq();

    let (glyph, switch) = switch_style(eq_row.on, selected);
    let title = Line::from(vec![
        Span::raw(" Graphic EQ  "),
        Span::styled(glyph, switch),
        Span::styled(if eq_row.on { " on " } else { " off " }, switch),
    ]);
    let border = if selected {
        Style::default().fg(Color::Cyan)
    } else {
        Style::default()
    };
    let block = Block::default()
        .borders(Borders::ALL)
        .border_style(border)
        .title(title);
    let inner = block.inner(area);
    f.render_widget(block, area);

    if inner.width < 10 || inner.height < 2 {
        return;
    }

    // Bottom line is the frequency labels; the rest is the bars.
    let bar_h = inner.height - 1;
    let dim = Style::default().fg(Color::DarkGray);

    for (band, &db) in eq_row.bands.iter().enumerate() {
        // Spread the bands across the full width rather than leaving the
        // division's remainder as dead space on the right.
        let x = inner.x + (inner.width as u32 * band as u32 / 10) as u16;
        let next = inner.x + (inner.width as u32 * (band as u32 + 1) / 10) as u16;
        let width = next.saturating_sub(x).max(1);
        let band_selected = selected && band == eq_row.band_cursor;

        let colour = if !eq_row.on {
            Color::DarkGray
        } else if band_selected {
            Color::Cyan
        } else if db > 0.0 {
            Color::Green
        } else if db < 0.0 {
            Color::Red
        } else {
            Color::DarkGray
        };

        // The whole `-EQ_SCALE_DB..=EQ_SCALE_DB` range maps onto the
        // column, so a band at the bottom is an empty column and one at
        // the top a full one.
        let state = SliderState::new(db as f64, -EQ_SCALE_DB as f64, EQ_SCALE_DB as f64);
        let slider = Slider::from_state(&state)
            .orientation(SliderOrientation::Vertical)
            .filled_symbol("█")
            .empty_symbol(" ")
            .filled_color(colour)
            .show_handle(false);
        f.render_widget(slider, Rect::new(x, inner.y, width, bar_h));

        let label_style = if band_selected {
            Style::default().fg(Color::Black).bg(Color::Cyan)
        } else if eq_row.on {
            Style::default().fg(Color::Gray)
        } else {
            dim
        };
        let label = if band_selected {
            format!("{db:+.1}")
        } else {
            EQ_FREQS[band].to_string()
        };
        f.render_widget(
            Paragraph::new(format!("{:^w$}", label, w = width as usize)).style(label_style),
            Rect::new(x, inner.y + bar_h, width, 1),
        );
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ratatui::backend::TestBackend;

    /// Render `app` at the given size and return the frame as plain text,
    /// one line per terminal row with trailing blanks trimmed.
    fn render(app: &App, width: u16, height: u16) -> String {
        let mut terminal = Terminal::new(TestBackend::new(width, height)).unwrap();
        terminal.draw(|f| draw(f, app)).unwrap();
        let buf = terminal.backend().buffer().clone();
        (0..buf.area.height)
            .map(|y| {
                let line: String = (0..buf.area.width).map(|x| buf[(x, y)].symbol()).collect();
                line.trim_end().to_string()
            })
            .collect::<Vec<_>>()
            .join("\n")
    }

    /// Renders the UI without a device and writes it to `target/ui-snapshot.txt`
    /// so the layout can be eyeballed. Not a golden test: it asserts only that
    /// the frame is non-empty, so it never blocks a deliberate UI change.
    #[test]
    fn writes_ui_snapshot() {
        let mut app = App::new(true);
        app.status = "dry run: showing defaults, not device state".into();

        let mut out = String::new();
        let mut shot = |title: &str, app: &App, w: u16, h: u16| {
            out.push_str(&format!("=== {title} ({w}x{h}) ===\n"));
            out.push_str(&render(app, w, h));
            out.push_str("\n\n");
        };

        shot("default, SBX master selected", &app, 80, 24);

        // An effect switched off keeps its level on screen, dimmed.
        app.selected = 3;
        app.rows[3].on = false;
        shot("Bass selected and switched off", &app, 80, 24);

        // The profile row: selected, and on a mode other than the default,
        // to show it draws no switch of its own.
        let profile = app
            .rows
            .iter()
            .position(|r| matches!(r.control, Control::SmartVolumeMode))
            .expect("the profile row is in the list");
        app.selected = profile;
        app.rows[profile].mode = SmartVolumeMode::Night;
        shot("Smart Volume profile selected", &app, 80, 24);
        app.rows[profile].mode = SmartVolumeMode::Normal;

        // The EQ row, on, with a few bands moved off flat.
        app.selected = app.rows.len() - 1;
        let eq = app.rows.last_mut().unwrap();
        eq.on = true;
        eq.bands = [6.0, 4.5, 0.0, -3.0, -6.0, 0.0, 2.0, 5.5, 8.0, -1.5];
        eq.band_cursor = 4;
        shot("EQ selected, bands set", &app, 80, 24);

        shot("narrow terminal", &app, 60, 20);

        std::fs::write("target/ui-snapshot.txt", &out).unwrap();
        assert!(out.contains("Sound Blaster E5"));
    }
}
