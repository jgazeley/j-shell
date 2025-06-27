# J-Shell CLI

A lightweight, cross-platform command-line interface module that can be embedded in both host (Windows/Linux) and Raspberry Pi Pico (RP2040) firmware.  Supports:

- **Plugin system** for registering command & menu “modules”  
- **Text-menu navigation** with key-selectable frames  
- **High-throughput “streamer” mode** alongside a small interactive shell  
- **Portable I/O abstraction**:  
  -On host: `fputs()` + `_getch()`  
  -On Pico: TinyUSB CDC via `tud_cdc_write_str()` + `getchar_timeout_us()`  

---

## Features

- **Modular commands**  
  Write your own `.c` file that calls `cli_command_register(…)` to expose new commands at startup.

- **Menu-driven UI**  
  Define one or more `menu_frame_t` tables and register them with `menu_init_root()` or via the plugin hooks.

- **Soft-exit / reboot**  
  Built-in “exit” command that either calls `exit(0)` on host or triggers `watchdog_reboot()` on RP2040.

- **Banner & versioning**  
  Customizable ASCII banner, build date, and platform string.

---

## Menu Example

==============J-Shell================  
An Open Source Command Line Interface

Version:    1.0.0  
Built:      Jun 26 2025  
Platform:   HOST

=== Main Menu ===  
 D) Debug Tests  
 H) Help  
 X) Exit  

### 1. Clone the repo

```bash
git clone https://github.com/jgazeley/j-shell.git
cd j-shell
```
You're on your own after that.
