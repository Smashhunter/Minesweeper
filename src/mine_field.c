#include "mine_field.h"

typedef struct 
{
    int x;
    int y;
} point;

static int is_availble_to_add(const Game *game, int x, int y)
{
    // Out of boundary check
    if(x >= game->cols || x < 0)
        return 0;
    if(y >= game->rows || y < 0)
        return 0;
    // Not Bomb
    if(game->field[y][x] == 'b')
        return 0;

    return 1;
}

// Auxiliary function to add numbers to field
static void add_around_mines(Game *game, point mine)
{
    int max_x =  mine.x+1, max_y = mine.y+1;
    for(int temp_y = mine.y-1; temp_y <= max_y; ++temp_y)
    {
        for(int temp_x = mine.x-1; temp_x <= max_x; ++temp_x){
            if(is_availble_to_add(game, temp_x, temp_y))
                game->field[temp_y][temp_x]++;
        }
    }

}

void init_field(Game *game)
{
    int number_of_cells = game->rows * game->cols;
    int number_of_mines = number_of_cells * 20 / 100; // = * 20%

    point *mines_cords = malloc(number_of_mines * sizeof(*mines_cords));
    int n = number_of_mines; // Buffered for while cycle
    int i = 0;
    point temp;
    while (n)
    {
        temp.x = rand() % game->cols;
        temp.y = rand() % game->rows;
        // Check dublicates
        for(int j = 0; j < i; ++j){
            if(temp.x == mines_cords[j].x && temp.y == mines_cords[j].y)
                continue;
        }
        mines_cords[i] = temp;
        ++i;
        --n;
    }
    // Fill with nums and bombs
    for(i = 0; i < number_of_mines; ++i){
        game->field[mines_cords[i].y][mines_cords[i].x] = 'b';
        add_around_mines(game, mines_cords[i]);
    }
    free(mines_cords);

    // Create invariant of field
    for(i = 0; i < game->rows; ++i){
        for(int j = 0; j < game->cols; ++j){
            if(game->field[i][j] != 'b')
                game->field[i][j] += '0';
        }
    }
    
}

void make_move(Game *game, int x, int y, enum move_type mt)
{
    return;
}
