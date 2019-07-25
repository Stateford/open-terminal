# OPEN-TERMIANL
-----------------
Simple application for opening new terminals from current path in i3 + urxvt

### *NOTE*: this only works for URXVT

## Installation
-----------------

#### (With Binary)
- Clone the project
- `make`
- `sudo cp open-terminal /usr/bin`
- edit your i3 config (sometimes located at `~/.config/i3/config`)
    - `bindsym $mod+Shift+Return exec open-terminal` 

#### (With Shell Script)
- Clone the project
- `cp open-terminal.sh ~/.config/i3/`
- edit your i3 config (sometimes located at `~/.config/i3/config`)
    - `bind sym $mod+Shift+Return exec bash ~/.config/i3/open-terminal.sh`

This is just a simple utility created for personal use with i3, but others are welcome to use it.
