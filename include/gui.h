#ifndef MY_GUI_H
#define MY_GUI_H

#include <ncurses.h>

#include "mine_field.h"

void init_color_pairs();
void draw_field(const Game *game);

#endif
