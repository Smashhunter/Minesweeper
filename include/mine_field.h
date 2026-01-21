#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include <stdlib.h>
#include <memory.h>

enum move_type {
    enter_cell,
    place_flag
};

enum gamestate {
    LOSE,
    CONTINUE,
    WIN
};

// With capital because its super entity
typedef struct{
    char **field;
    char **fogged;
    int rows;
    int cols;
    int flags_count;
    int mines_count;
} Game; 

typedef struct 
{
    int x;
    int y;
} point;


// Field supposed to be 2-d char array filled with '\0' chars
void init_field(Game *game); /* Not supposed to resize array of field*/
void init_fogged(Game *game);
enum gamestate make_move(Game *game, point move_cords, enum move_type mt);

#endif
