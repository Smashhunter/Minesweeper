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
- Space = add flag to selected cell
- Enter = Open *safe* cell

## Symbols

// TODO: Document symbols

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

[ ] Coloring
[ ] Score system
[ ] Difficulty levels
[ ] Windows build
