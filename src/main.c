#include <ncurses.h>
#include <memory.h>

#include "mine_field.h"

int main()
{
    initscr();

    if(!has_colors()){
        endwin();
        fprintf(stderr, "Your terminal dont support coloring!");
        return 1;
    }
    start_color();

    // init game field
    Game game;
    getmaxyx(stdscr, game.rows, game.cols);
    game.field =  malloc(game.rows*sizeof(*game.field));
    for(int i = 0; i < game.rows; ++i){
        game.field[i] = calloc(game.cols, sizeof(*game.field[i]));
    }
    init_field(&game);

    //Init color pairs for bombs and flags;
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // for ones, two's and so on
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_BLACK, COLOR_WHITE); // for bombs
    init_pair(10,COLOR_BLACK, COLOR_GREEN); // for flags

    //Draw full field
    for(int i = 0; i < game.rows; ++i){
        for(int j = 0; j < game.cols; ++j){
            move(i, j);
            
            if(game.field[i][j] > '0' && game.field[i][j] < '9'){
                attrset(COLOR_PAIR(game.field[i][j] - '0'));
                addch(game.field[i][j]);
            } else if(game.field[i][j] == '0') {
                attrset(A_DIM | COLOR_PAIR(0));
                addch('.');
            } else if (game.field[i][j] == 'b') {
                attrset(A_BOLD | COLOR_PAIR(9));
                addch(game.field[i][j]);
            } else if (game.field[i][j] == 'f') {
                attrset(A_BOLD | COLOR_PAIR(10));
                addch(game.field[i][j]);
            }
        }
    }
    refresh();
    getch();
    endwin();
    return 0;
}
