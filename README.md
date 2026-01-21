# Minesweeper

Classic arcade game on pure C.

This game is uses ncurses as main library to output game.
Game supposed to be runned in console without additional parametrs. (Can change in future)

## Running

``` bash
(cwd) ./minesweeper
```

## Controls

- Arrows = move cursor
- x = add flag to selected cell
- z = Open *safe* cell

## Symbols

- b - bomb/mine
- ? - unckown symbol
- f - flag
- [1..9] - obviously number of connected with this cell bombs

## Building

Now build is tested only on Linux systems (Debian-based).
That means probably all dependencies already installed in your sysyem so you can write this:

``` bash
#debug compilation
make
make debug
#release version
make release
# for static compilation (used in repo releases)
make static
```

## Additional features (in plans)

- [x] Coloring
- [ ] Score system
- [ ] Difficulty levels
- [ ] Windows build
