#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include <stdlib.h>
#include <memory.h>

enum move_type {
    enter_cell,
    place_flag
};

// With capital because its super entity
typedef struct{
    char **field;
    int rows;
    int cols;
} Game; 

// Field supposed to be 2-d char array filled with '\0' chars
void init_field(Game *game); /* Not supposed to resize array of field*/
void make_move(Game *game, int x, int y, enum move_type mt);

#endif
