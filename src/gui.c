#include "gui.h"

void init_color_pairs()
{
    //Init color pairs for bombs and flags;
    // Zero pair is used for zeros and question marks
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // for ones, two's and so on
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_CYAN);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_BLACK, COLOR_WHITE); // for bombs
    init_pair(10,COLOR_BLACK, COLOR_GREEN); // for flags
}

void draw_field(const Game *game)
{
    clear();
    for(int i = 0; i < game -> rows; ++i){
        for(int j = 0; j < game -> cols; ++j){
            move(i, j);
            
            if(game->fogged[i][j] > '0' && game->fogged[i][j] < '9'){
                attrset(COLOR_PAIR(game->fogged[i][j] - '0'));
                addch(game->fogged[i][j]);
            } else if(game->fogged[i][j] == '0') {
                attrset(A_DIM | COLOR_PAIR(0));
                addch(' ');
            } else if (game->fogged[i][j] == 'b') {
                attrset(A_BOLD | COLOR_PAIR(9) | A_BLINK);
                addch(game->fogged[i][j]);
            } else if (game->fogged[i][j] == 'f') {
                attrset(A_BOLD | COLOR_PAIR(10));
                addch(game->fogged[i][j]);
            } else if (game->fogged[i][j] == '?') {
                attrset(A_DIM | COLOR_PAIR(0));
                addch(game->fogged[i][j]);
            }
        }
    }
    refresh();
}
