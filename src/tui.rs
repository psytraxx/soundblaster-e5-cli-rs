//! Interactive terminal UI, shown when the CLI is run with no subcommand.
//!
//! Every control maps to one parameter in [`crate::transport::id`]. Rows
//! carry the same [`Confidence`] the wire table does, so a value that has
//! never been seen on real hardware is visibly marked rather than presented
//! as settled.
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
use crate::transport::Confidence;
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
    /// Shown but not backed by the normal `Level`/`Toggle` write path.
    /// Currently only the SBX master row, which uses its own `0x23`-opcode
    /// read/write -- see [`App::write_sbx_master`].
    Unavailable,
}

/// Center frequency label for each of the ten EQ bands.
const EQ_FREQS: [&str; 10] = [
    "31Hz", "62Hz", "125Hz", "250Hz", "500Hz", "1kHz", "2kHz", "4kHz", "8kHz", "16kHz",
];

/// Label of the SBX master row, which several places match on to route it
/// to its own read/write path. See [`Row::is_sbx_master`].
const SBX_MASTER: &str = "SBX master";

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
    confidence: Confidence,
}

impl Row {
    fn is_toggle(&self) -> bool {
        matches!(self.control, Control::Toggle { .. })
    }

    /// The SBX master row, which is `Unavailable` because it uses its own
    /// `0x23` opcode rather than the `Level`/`Toggle` write path, but still
    /// behaves as an on/off switch everywhere the UI is concerned.
    fn is_sbx_master(&self) -> bool {
        self.control == Control::Unavailable && self.label == SBX_MASTER
    }

    /// True for anything the user flips on and off, however it is wired.
    fn is_switch(&self) -> bool {
        self.is_toggle() || self.is_sbx_master()
    }

    /// Step size for one arrow-key press.
    fn step(&self) -> f32 {
        match self.control {
            Control::Toggle { .. } | Control::Unavailable => 1.0,
            Control::EqBands => 0.5,
            Control::Level { .. } => 0.05,
        }
    }

    fn range(&self) -> (f32, f32) {
        match self.control {
            Control::Toggle { .. } | Control::Unavailable => (0.0, 1.0),
            Control::EqBands => (-12.0, 12.0),
            Control::Level { .. } => (0.0, 1.0),
        }
    }

    /// Position within the row's range, for the gauge.
    fn ratio(&self) -> f64 {
        let (lo, hi) = self.range();
        (((self.value - lo) / (hi - lo)) as f64).clamp(0.0, 1.0)
    }

    fn display(&self) -> String {
        match self.control {
            Control::Toggle { .. } => {
                if self.value >= 0.5 {
                    "on".into()
                } else {
                    "off".into()
                }
            }
            Control::EqBands => format!(
                "{} {:+.1}dB",
                EQ_FREQS[self.band_cursor], self.bands[self.band_cursor]
            ),
            Control::Level { .. } => format!("{:.0}%", self.value * 100.0),
            Control::Unavailable => {
                if self.value >= 0.5 {
                    "on".into()
                } else {
                    "off".into()
                }
            }
        }
    }
}

/// Build a row with the EQ-only fields defaulted; only `rows()` needs those.
fn row(label: &'static str, control: Control, value: f32, confidence: Confidence) -> Row {
    Row {
        label,
        control,
        value,
        bands: [0.0; 10],
        band_cursor: 0,
        confidence,
    }
}

/// The rows the UI shows, in display order.
fn rows() -> Vec<Row> {
    use Confidence::{Captured, Derived};

    /// An enable toggle followed by its level, the pairing every effect uses.
    fn effect(
        name: &'static str,
        enable_label: &'static str,
        feature: Feature,
        enable: u32,
        level: u32,
        default: f32,
        level_conf: Confidence,
    ) -> [Row; 2] {
        [
            row(
                enable_label,
                Control::Toggle {
                    feature,
                    param: enable,
                },
                1.0,
                Confidence::Derived,
            ),
            row(
                name,
                Control::Level {
                    feature,
                    param: level,
                },
                default,
                level_conf,
            ),
        ]
    }

    // Replaced by the real state on startup; see `App::refresh_from_device`.
    let mut rows = vec![row(SBX_MASTER, Control::Unavailable, 0.0, Captured)];

    rows.extend(effect(
        "Surround",
        "Surround on",
        Feature::EffectsSimpleSurround,
        SimpleSurround::Enable as u32,
        SimpleSurround::Level as u32,
        0.12,
        Derived,
    ));
    rows.extend(effect(
        "Crystalizer",
        "Crystalizer on",
        Feature::EffectsCrystalizer,
        Crystalizer::Enable as u32,
        Crystalizer::Level as u32,
        0.5,
        Derived,
    ));
    rows.extend(effect(
        "Bass",
        "Bass on",
        Feature::EffectsXBass,
        XBass::Enable as u32,
        XBass::Strength as u32,
        0.3,
        Captured,
    ));
    rows.extend(effect(
        "Dialog Plus",
        "Dialog Plus on",
        Feature::EffectsDialogPlus,
        DialogPlus::Enable as u32,
        DialogPlus::Strength as u32,
        0.5,
        Derived,
    ));
    rows.extend(effect(
        "Smart Volume",
        "Smart Volume on",
        Feature::EffectsSmartVolume,
        SmartVolume::Enable as u32,
        SmartVolume::Strength as u32,
        0.74,
        Derived,
    ));

    rows.push(row(
        "EQ on",
        Control::Toggle {
            feature: Feature::EffectsGraphicEQ,
            param: GraphicEq::Enable as u32,
        },
        0.0,
        Derived,
    ));

    rows.push(row("EQ bands", Control::EqBands, 0.0, Derived));
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
        // The SBX master row has no `0x20` selector -- it uses its own
        // `0x23 0x23` opcode -- so handle it before the general match
        // below falls through to a no-op.
        if self.rows[self.selected].is_sbx_master() {
            self.write_sbx_master(dev);
            return;
        }

        let row = &self.rows[self.selected];
        let result = match row.control {
            Control::Level { feature, param } => dev.set_level_raw(feature, param, row.value),
            Control::Toggle { feature, param } => {
                dev.set_enable_raw(feature, param, row.value >= 0.5)
            }
            Control::EqBands => dev.set_eq_band(row.band_cursor as u8, row.bands[row.band_cursor]),
            Control::Unavailable => return,
        };
        self.status = match result {
            Ok(()) => format!("{} = {}", row.label, row.display()),
            Err(e) => format!("{}: {e}", row.label),
        };
    }

    /// Send the SBX master write and adopt the state the device reports
    /// back, rather than assuming the write took. See
    /// [`crate::SoundBlasterE5::set_sbx_master`].
    fn write_sbx_master(&mut self, dev: &mut SoundBlasterE5) {
        let want = self.rows[self.selected].value >= 0.5;
        match dev.set_sbx_master(want) {
            Ok(got) => {
                self.rows[self.selected].value = if got { 1.0 } else { 0.0 };
                self.status = format!("SBX master = {}", if got { "on" } else { "off" });
            }
            Err(e) => self.status = format!("SBX master: {e}"),
        }
    }

    /// Left/right on a normal row adjusts its value; on the EQ row it moves
    /// which band is being edited (see `adjust_band`).
    fn adjust(&mut self, dir: f32, dev: &mut SoundBlasterE5) {
        match self.rows[self.selected].control {
            Control::Unavailable if self.rows[self.selected].is_sbx_master() => {
                self.toggle(dev);
            }
            Control::Unavailable => {
                self.status = "no known wire encoding yet".into();
            }
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
            row.value = if row.value >= 0.5 { 0.0 } else { 1.0 };
            self.write_selected(dev);
        }
    }

    /// Pull each row's live value from the device, replacing the built-in
    /// defaults in [`rows`]. Best-effort: a row whose read fails (dry-run,
    /// no device, or a parameter the `0x26` path doesn't cover -- EQ bands
    /// and the master switch aren't confirmed at the individual-band level)
    /// just keeps its default and is left alone.
    ///
    /// See `reverse/e5-control-protocol.md`, "Read path", and
    /// [`crate::transport::Transport::get_float`].
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
                // Only the SBX master row is `Unavailable` with a read to
                // attempt; the check keeps this from matching some future
                // no-encoding row that has no read either.
                Control::Unavailable if row.is_sbx_master() => match dev.get_sbx_master() {
                    Ok(on) => {
                        row.value = if on { 1.0 } else { 0.0 };
                        read_ok += 1;
                    }
                    Err(_) => read_err += 1,
                },
                Control::EqBands | Control::Unavailable => {}
            }
        }

        self.status = if read_err == 0 {
            format!("loaded {read_ok} values from device")
        } else {
            format!("loaded {read_ok} values from device, {read_err} unread (kept defaults)")
        };
    }
}

/// Run the interactive UI until the user quits.
pub fn run(dev: &mut SoundBlasterE5) -> Result<()> {
    let mut app = App::new(dev.is_dry_run());
    app.refresh_from_device(dev);

    enable_raw_mode()?;
    let mut out = io::stdout();
    out.execute(EnterAlternateScreen)?;
    out.execute(EnableMouseCapture)?;
    let backend = CrosstermBackend::new(out);
    let mut terminal = Terminal::new(backend)?;

    let result = event_loop(&mut terminal, &mut app, dev);

    // Restore the terminal even if the loop failed, so a crash cannot
    // leave the shell in raw mode.
    disable_raw_mode()?;
    terminal.backend_mut().execute(LeaveAlternateScreen)?;
    terminal.backend_mut().execute(DisableMouseCapture)?;
    terminal.show_cursor()?;

    result
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
                Constraint::Length(3),
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
            let (glyph, colour) = if row.value >= 0.5 {
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

        // Mark values that have never been seen on real hardware.
        if row.confidence == Confidence::Derived {
            f.render_widget(
                Paragraph::new(" ?").style(Style::default().fg(Color::DarkGray)),
                cols[3],
            );
        }
    }
}
