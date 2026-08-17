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
use ratatui::widgets::{Block, Borders, Gauge, Paragraph};
use tui_slider::{Slider, SliderOrientation, SliderState};

use crate::proto::{
    Crystalizer, DialogPlus, Feature, GraphicEq, SimpleSurround, SmartVolume, XBass,
};
use crate::{Result, SoundBlasterE5};

/// What a row writes when it changes.
#[derive(Clone, Copy, PartialEq, Eq)]
enum Control {
    /// A normalized `0.0..=1.0` level.
    Level { feature: Feature, param: u32 },
    /// An on/off toggle.
    Toggle { feature: Feature, param: u32 },
    /// All ten graphic-EQ bands, drawn as their own panel below the row
    /// list rather than inline. Left/right move a cursor between bands.
    EqBands,
    /// The SBX master switch. Behaves as an on/off switch everywhere the UI
    /// is concerned, but has no `0x20` selector: it rides its own `0x23`
    /// opcode -- see [`App::write_sbx_master`].
    SbxMaster,
}

/// Center frequency label for each of the ten EQ bands.
const EQ_FREQS: [&str; 10] = [
    "31Hz", "62Hz", "125Hz", "250Hz", "500Hz", "1kHz", "2kHz", "4kHz", "8kHz", "16kHz",
];

struct Row {
    label: &'static str,
    control: Control,
    /// Current value: a level, 0/1 for a toggle, or dB for a band.
    /// Unused when `control` is `EqBands`, which keeps its own array.
    value: f32,
    /// The ten band gains, in dB. Unused outside `Control::EqBands`.
    bands: [f32; 10],
    /// Which band left/right moves, when `control` is `EqBands`.
    band_cursor: usize,
}

impl Row {
    /// True for anything the user flips on and off, however it is wired.
    fn is_switch(&self) -> bool {
        matches!(self.control, Control::Toggle { .. } | Control::SbxMaster)
    }

    /// Step size for one arrow-key press.
    fn step(&self) -> f32 {
        match self.control {
            Control::Toggle { .. } | Control::SbxMaster => 1.0,
            Control::EqBands => 0.5,
            Control::Level { .. } => 0.05,
        }
    }

    fn range(&self) -> (f32, f32) {
        match self.control {
            Control::Toggle { .. } | Control::SbxMaster => (0.0, 1.0),
            Control::EqBands => (-12.0, 12.0),
            Control::Level { .. } => (0.0, 1.0),
        }
    }

    /// Position within the row's range, for the gauge.
    fn ratio(&self) -> f64 {
        let (lo, hi) = self.range();
        (((self.value - lo) / (hi - lo)) as f64).clamp(0.0, 1.0)
    }

    /// True when a switch row is on. Levels ride the same field, so this is
    /// only meaningful where [`Row::is_switch`] holds.
    fn is_on(&self) -> bool {
        self.value >= 0.5
    }

    fn display(&self) -> String {
        match self.control {
            Control::Toggle { .. } | Control::SbxMaster => {
                if self.is_on() { "on" } else { "off" }.into()
            }
            Control::EqBands => format!(
                "{} {:+.1}dB",
                EQ_FREQS[self.band_cursor], self.bands[self.band_cursor]
            ),
            Control::Level { .. } => format!("{:.0}%", self.value * 100.0),
        }
    }
}

/// Build a row with the EQ-only fields defaulted; only `rows()` needs those.
fn row(label: &'static str, control: Control, value: f32) -> Row {
    Row {
        label,
        control,
        value,
        bands: [0.0; 10],
        band_cursor: 0,
    }
}

/// The rows the UI shows, in display order.
fn rows() -> Vec<Row> {
    /// An enable toggle followed by its level, the pairing every effect uses.
    fn effect(
        name: &'static str,
        enable_label: &'static str,
        feature: Feature,
        enable: u32,
        level: u32,
        default: f32,
    ) -> [Row; 2] {
        [
            row(
                enable_label,
                Control::Toggle {
                    feature,
                    param: enable,
                },
                1.0,
            ),
            row(
                name,
                Control::Level {
                    feature,
                    param: level,
                },
                default,
            ),
        ]
    }

    // Replaced by the real state on startup; see `App::refresh_from_device`.
    let mut rows = vec![row("SBX master", Control::SbxMaster, 0.0)];

    rows.extend(effect(
        "Surround",
        "Surround on",
        Feature::EffectsSimpleSurround,
        SimpleSurround::Enable as u32,
        SimpleSurround::Level as u32,
        0.12,
    ));
    rows.extend(effect(
        "Crystalizer",
        "Crystalizer on",
        Feature::EffectsCrystalizer,
        Crystalizer::Enable as u32,
        Crystalizer::Level as u32,
        0.5,
    ));
    rows.extend(effect(
        "Bass",
        "Bass on",
        Feature::EffectsXBass,
        XBass::Enable as u32,
        XBass::Strength as u32,
        0.3,
    ));
    rows.extend(effect(
        "Dialog Plus",
        "Dialog Plus on",
        Feature::EffectsDialogPlus,
        DialogPlus::Enable as u32,
        DialogPlus::Strength as u32,
        0.5,
    ));
    rows.extend(effect(
        "Smart Volume",
        "Smart Volume on",
        Feature::EffectsSmartVolume,
        SmartVolume::Enable as u32,
        SmartVolume::Strength as u32,
        0.74,
    ));

    rows.push(row(
        "EQ on",
        Control::Toggle {
            feature: Feature::EffectsGraphicEQ,
            param: GraphicEq::Enable as u32,
        },
        0.0,
    ));

    rows.push(row("EQ bands", Control::EqBands, 0.0));
    rows
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

    /// Apply the selected row's current value to the device.
    fn write_selected(&mut self, dev: &mut SoundBlasterE5) {
        let row = &self.rows[self.selected];
        let result = match row.control {
            Control::Level { feature, param } => dev.set_level_raw(feature, param, row.value),
            Control::Toggle { feature, param } => dev.set_enable_raw(feature, param, row.is_on()),
            Control::EqBands => dev.set_eq_band(row.band_cursor as u8, row.bands[row.band_cursor]),
            // The master switch has no `0x20` selector -- it rides its own
            // `0x23 0x23` opcode, and answers with the state it ended up in.
            Control::SbxMaster => {
                let got = dev.set_sbx_master(row.is_on());
                if let Ok(on) = got {
                    self.rows[self.selected].value = f32::from(u8::from(on));
                }
                got.map(|_| ())
            }
        };

        let row = &self.rows[self.selected];
        self.status = match result {
            Ok(()) => format!("{} = {}", row.label, row.display()),
            Err(e) => format!("{}: {e}", row.label),
        };
    }

    /// Left/right on a normal row adjusts its value; on the EQ row it moves
    /// which band is being edited (see `adjust_band`).
    fn adjust(&mut self, dir: f32, dev: &mut SoundBlasterE5) {
        match self.rows[self.selected].control {
            // A switch has nothing to slide; left/right just flips it.
            Control::SbxMaster => self.toggle(dev),
            Control::EqBands => self.move_band_cursor(dir),
            _ => {
                let row = &mut self.rows[self.selected];
                let (lo, hi) = row.range();
                let step = row.step();
                row.value = (row.value + dir * step).clamp(lo, hi);
                // Kill float drift so 0.05 steps land on clean values.
                row.value = (row.value / step).round() * step;
                self.write_selected(dev);
            }
        }
    }

    fn move_band_cursor(&mut self, dir: f32) {
        let row = &mut self.rows[self.selected];
        let cursor = row.band_cursor as isize + dir.signum() as isize;
        row.band_cursor = cursor.clamp(0, 9) as usize;
    }

    /// Raise or lower the EQ band under the cursor. Only meaningful on the
    /// EQ bands row; a no-op elsewhere.
    fn adjust_band(&mut self, dir: f32, dev: &mut SoundBlasterE5) {
        if !matches!(self.rows[self.selected].control, Control::EqBands) {
            return;
        }
        let row = &mut self.rows[self.selected];
        let (lo, hi) = row.range();
        let step = row.step();
        let v = &mut row.bands[row.band_cursor];
        *v = (*v + dir * step).clamp(lo, hi);
        *v = (*v / step).round() * step;
        self.write_selected(dev);
    }

    fn toggle(&mut self, dev: &mut SoundBlasterE5) {
        if self.rows[self.selected].is_switch() {
            let row = &mut self.rows[self.selected];
            row.value = if row.is_on() { 0.0 } else { 1.0 };
            self.write_selected(dev);
        }
    }

    /// Pull each row's live value from the device, replacing the built-in
    /// defaults in [`rows`]. Best-effort: a row whose read fails -- dry-run,
    /// no device, or the EQ band panel, which has no single value to read --
    /// keeps its default and is left alone.
    fn refresh_from_device(&mut self, dev: &mut SoundBlasterE5) {
        if dev.is_dry_run() {
            self.status = "dry run: showing defaults, not device state".into();
            return;
        }

        let mut read_ok = 0;
        let mut read_err = 0;
        for row in &mut self.rows {
            match row.control {
                Control::Level { feature, param } | Control::Toggle { feature, param } => {
                    match dev.get_level_raw(feature, param) {
                        Ok(v) => {
                            row.value = v;
                            read_ok += 1;
                        }
                        Err(_) => read_err += 1,
                    }
                }
                Control::SbxMaster => match dev.get_sbx_master() {
                    Ok(on) => {
                        row.value = f32::from(u8::from(on));
                        read_ok += 1;
                    }
                    Err(_) => read_err += 1,
                },
                // No single value to read: the bands are read individually
                // and the panel keeps its own array.
                Control::EqBands => {}
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
    let chunks = Layout::default()
        .direction(Direction::Vertical)
        .constraints([
            Constraint::Length(1),
            Constraint::Min(3),
            Constraint::Length(EQ_PANEL_HEIGHT),
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
        Span::raw(" adjust / pick band   "),
        Span::styled("+-", Style::default().fg(Color::Cyan)),
        Span::raw(" band gain   "),
        Span::styled("space", Style::default().fg(Color::Cyan)),
        Span::raw(" toggle   "),
        Span::styled("q", Style::default().fg(Color::Cyan)),
        Span::raw(" quit"),
    ]);
    let status = Paragraph::new(vec![Line::from(app.status.clone()), help]);
    f.render_widget(status, chunks[3]);
}

const EQ_PANEL_HEIGHT: u16 = 9;

/// A 10-band equalizer: one vertical `tui-slider` per band (range
/// `-12..=12` dB, bottom-filled), with frequency labels underneath.
fn draw_eq_panel(f: &mut ratatui::Frame, app: &App, area: Rect) {
    let Some(eq_row) = app
        .rows
        .iter()
        .find(|r| matches!(r.control, Control::EqBands))
    else {
        return;
    };
    let selected = matches!(app.rows[app.selected].control, Control::EqBands);

    let block = Block::default().borders(Borders::ALL).title(" Graphic EQ ");
    let inner = block.inner(area);
    f.render_widget(block, area);
    if inner.width < 10 || inner.height < 2 {
        return;
    }

    let bar_area_h = inner.height.saturating_sub(1);
    let col_w = (inner.width / 10).max(1);

    for (band, &db) in eq_row.bands.iter().enumerate() {
        let x = inner.x + band as u16 * col_w;
        if x >= inner.x + inner.width {
            break;
        }
        let width = col_w.min(inner.x + inner.width - x);
        let col = Rect::new(x, inner.y, width, bar_area_h);

        let band_selected = selected && band == eq_row.band_cursor;
        let colour = if band_selected {
            Color::Cyan
        } else if db > 0.0 {
            Color::Green
        } else if db < 0.0 {
            Color::Red
        } else {
            Color::DarkGray
        };

        let state = SliderState::new(db as f64, -12.0, 12.0);
        let slider = Slider::from_state(&state)
            .orientation(SliderOrientation::Vertical)
            .filled_symbol("█")
            .empty_symbol(" ")
            .filled_color(colour)
            .show_handle(false);
        f.render_widget(slider, col);

        let label_y = inner.y + bar_area_h;
        let label_area = Rect::new(x, label_y, width, 1);
        let label_style = if band_selected {
            Style::default().fg(Color::Black).bg(Color::Cyan)
        } else {
            Style::default().fg(Color::Gray)
        };
        f.render_widget(
            Paragraph::new(format!("{:^w$}", EQ_FREQS[band], w = width as usize))
                .style(label_style),
            label_area,
        );
    }
}

fn draw_rows(f: &mut ratatui::Frame, app: &App, area: Rect) {
    let block = Block::default().borders(Borders::ALL);
    let inner = block.inner(area);
    f.render_widget(block, area);

    // One line per row; scroll so the selection stays visible.
    let height = inner.height as usize;
    let first = app.selected.saturating_sub(height.saturating_sub(1));
    let visible = app.rows.iter().enumerate().skip(first).take(height);

    for (i, (idx, row)) in visible.enumerate() {
        let y = inner.y + i as u16;
        let line = Rect::new(inner.x, y, inner.width, 1);
        let cols = Layout::default()
            .direction(Direction::Horizontal)
            .constraints([
                Constraint::Length(16),
                Constraint::Min(10),
                Constraint::Length(10),
            ])
            .split(line);

        let selected = idx == app.selected;
        let label_style = if selected {
            Style::default().fg(Color::Black).bg(Color::Cyan)
        } else {
            Style::default()
        };
        f.render_widget(
            Paragraph::new(format!(" {}", row.label)).style(label_style),
            cols[0],
        );

        if row.is_switch() {
            let (glyph, colour) = if row.is_on() {
                ("[x]", Color::Green)
            } else {
                ("[ ]", Color::DarkGray)
            };
            f.render_widget(
                Paragraph::new(glyph).style(Style::default().fg(colour)),
                cols[1],
            );
        } else if matches!(row.control, Control::EqBands) {
            f.render_widget(
                Paragraph::new("see panel below").style(Style::default().fg(Color::DarkGray)),
                cols[1],
            );
        } else {
            let colour = if row.value >= 0.5 {
                Color::Green
            } else {
                Color::Blue
            };
            f.render_widget(
                Gauge::default()
                    .ratio(row.ratio())
                    .label("")
                    .gauge_style(Style::default().fg(colour)),
                cols[1],
            );
        }

        f.render_widget(Paragraph::new(format!("{:>9}", row.display())), cols[2]);
    }
}
