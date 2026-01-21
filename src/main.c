#include <ncurses.h>
#include <memory.h>

#include "mine_field.h"
#include "gui.h"

enum { key_escape = 27 };

static void check(int *coord, int max)
{
    if(*coord < 0)
        *coord+=max;
    else if (*coord > max)
        *coord -= max;
}

void move_cursor(const Game *game, point *cursor_pos, int dx, int dy)
{
    cursor_pos->x += dx;
    check(&cursor_pos->x, game->cols);
    cursor_pos->y += dy;
    check(&cursor_pos->y, game->rows);
    move(cursor_pos->y, cursor_pos->x);
}

int main()
{
    initscr();

    if(!has_colors()){
        endwin();
        fprintf(stderr, "Your terminal doesn't support coloring!");
        return 1;
    }
    start_color();

    cbreak();
    keypad(stdscr, 1);
    noecho();
    

    // init game field
    Game game;
    getmaxyx(stdscr, game.rows, game.cols);
    game.field =  malloc(game.rows*sizeof(*game.field));
    for(int i = 0; i < game.rows; ++i){
        game.field[i] = calloc(game.cols, sizeof(*game.field[i]));
    }
    init_field(&game);

    init_color_pairs();

    draw_field(&game);
    curs_set(2);

    int key;
    // Cords for cursor point
    point cur_cords = {game.cols / 2, game.rows / 2};
    move(cur_cords.y, cur_cords.x);
    while((key = getch()) != key_escape){
        switch (key){
        case KEY_UP:
            move_cursor(&game, &cur_cords, 0, -1);
            break;
        case KEY_DOWN:
            move_cursor(&game, &cur_cords, 0, 1);
            break;
        case KEY_LEFT:
            move_cursor(&game, &cur_cords, -1, 0);
            break;
        case KEY_RIGHT:
            move_cursor(&game, &cur_cords, 1, 0);
            break;
        }
        refresh();
    }
    endwin();
    return 0;
}
