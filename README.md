# qdmenu

A dmenu like launcher program written in QT/QML. It can be used as a drop-in replacement for dmenu for example in i3 and
other tiling window manager. There is a PKGBUILD package submitted to AUR (https://aur.archlinux.org/packages/qdmenu/)

# Features

 - Fast & simple
 - *.desktop file parsing and displaying:
    - Locale aware name display if defined
    - Users local and systemwide applications/ folders are merged, systemwide desktop files are overriden with the users files
    - Icon display
    - Desktop files with NoDisplay=true are filtered out
    - Desktop files with Terminal=true are launched in the default terminal
 - Searching:
    - Searching filters the list on: binary name, name and comment from desktop file
    - If no results are found the command is interpreted and executed as-is
 - Keyboard driven:
    - Escape quits
    - Arrow keys move the selection
    - Enter starts the given command / selected app
    - Mouse also supported

# Screenshots
![Main screen](/screenshot1.jpg "Main screen")
![Searching](/screenshot2.jpg "Searching")

# Contribution
This is my first public project on github, i know the code lacks comments but i think its readable.
There are some codeing guidelines which i tried to follow in this project, the most important ares:
 - 80 column width
 - 4 spaces and no tabs
But theese arent mandatory either, if you contribute please try to keep your code readable and if something
is not clear then put a comment on it, thnx ;)

# TODO
 - Config file in ~/.local/config/qdmenu/config, with config options:
    - Icon / Grid item size
    - Background color, text color, text background
    - Custom unknown icon
    - Custom binary icon
    - display NoDisplay entries true/false
    - display plain binaries by default true/false
    - modifier keys remap

- Add modifier key for sudo/gksu/kdesu starting
- Raw binary listing
- Add modifier key for switching *.desktop file listing mode ( currently implemented ) and raw binary listing mode
