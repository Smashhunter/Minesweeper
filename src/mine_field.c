#include "mine_field.h"

#include <stdio.h>

static int is_available_to_add(const Game *game, int x, int y)
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
    // Process all cell around mine with 3x3 square
    fprintf(stderr, "Processing mine at (%d, %d)\n", mine.x, mine.y);
    for(int temp_y = mine.y - 1; temp_y <= mine.y + 1; ++temp_y)
    {
        for(int temp_x = mine.x - 1; temp_x <= mine.x + 1; ++temp_x)
        {
            if(is_available_to_add(game, temp_x, temp_y)){
                fprintf(stderr, "  Incrementing cell (%d, %d)\n", temp_x, temp_y);
                game->field[temp_y][temp_x]++;
            }
        }
    }
}
void init_field(Game *game)
{
    int number_of_cells = game->rows * game->cols;
    int number_of_mines = number_of_cells * 20 / 100; // = * 20%

    // Get mines cords using Ficher-Yets algorithm
    point *mines_cords = malloc(number_of_mines * sizeof(*mines_cords));
    
    // First number_of_mines cords
    for (int i = 0; i < number_of_mines; i++) {
        mines_cords[i].x = i % game->cols;
        mines_cords[i].y = i / game->cols;
    }

    // Replace with random cords
    for (int i = number_of_mines; i < number_of_cells; i++) {
        int r = rand() % (i + 1);
    
        if (r < number_of_mines) {
            mines_cords[r].x = i % game->cols;
            mines_cords[r].y = i / game->cols;
        }
    }

    // Fill with nums and bombs
    for(int i = 0; i < number_of_mines; ++i){
        game->field[mines_cords[i].y][mines_cords[i].x] = 'b';
        add_around_mines(game, mines_cords[i]); // Дублирование здесь так как в списке оказалась копия мины
    }
    free(mines_cords);

    // Create invariant of field
    for(int i = 0; i < game->rows; ++i){
        for(int j = 0; j < game->cols; ++j){
            if(game->field[i][j] != 'b')
                game->field[i][j] += '0';
        }
    }
    
}

void make_move(Game *game, point move_cords, enum move_type mt)
{
    return;
}

