#include "mine_field.h"

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

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
    for(int temp_y = mine.y - 1; temp_y <= mine.y + 1; ++temp_y)
    {
        for(int temp_x = mine.x - 1; temp_x <= mine.x + 1; ++temp_x)
        {
            if(is_available_to_add(game, temp_x, temp_y)){
                game->field[temp_y][temp_x]++;
            }
        }
    }
}

void init_field(Game *game)
{
    int number_of_cells = game->rows * game->cols;
    int number_of_mines = number_of_cells * 5 / 100; // = * 5%
    game->mines_count = number_of_mines;
    game->flags_count = 0;

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

void init_fogged(Game *game)
{
    // Create invariant of fogged field
    for(int i = 0; i < game->rows; ++i){
        for(int j = 0; j < game->cols; ++j){
            game->fogged[i][j] += '?';
        }
    }
}

static void handle_flag(Game *game, point move_cords)
{
    if(game->fogged[move_cords.y][move_cords.x] == '?'){
        game->fogged[move_cords.y][move_cords.x] = 'f';
        game->flags_count++;
    } else if (game->fogged[move_cords.y][move_cords.x] == 'f') {
        game->fogged[move_cords.y][move_cords.x] = '?';
        game->flags_count--;
    }
}

static void open_zeros(Game *game, point check_point){
    // Process all cell around mine with 3x3 square
    for(int temp_y = check_point.y - 1; temp_y <= check_point.y + 1; ++temp_y)
    {
        for(int temp_x = check_point.x - 1; temp_x <= check_point.x + 1; ++temp_x)
        {
           if (is_available_to_add(game, temp_x, temp_y)) 
           {
                if (game->fogged[temp_y][temp_x] == '?') {
                    game->fogged[temp_y][temp_x] = game->field[temp_y][temp_x];
                    
                    if (game->field[temp_y][temp_x] == '0') {
                        point tmp = {temp_x, temp_y};
                        open_zeros(game, tmp);
                    }
                }
            }
        }
    }
}

static enum gamestate handle_enter_cell(Game *game, point move_cords)
{
    int x = move_cords.x, y = move_cords.y;
    char **field = game->field;
    char **fogged = game->fogged;

    if(field[y][x] == 'f'){
        game->flags_count--;
    }

    if(field[y][x] == 'b'){
        return LOSE;
    } else if (field[y][x] == '0') {
        open_zeros(game, move_cords);
    } else {
        fogged[y][x] = field[y][x];
    }
    return CONTINUE;
}

// 0 not win
static enum gamestate check_win(const Game *game){
    if (game ->flags_count != game ->mines_count)
        return CONTINUE;
    
    for(int i = 0; i < game->rows; ++i){
        for(int j = 0; j < game->cols; ++j){
            if(game->field[i][j] == 'b' && game->fogged[i][j] != 'f')
                return CONTINUE;
            if(game->fogged[i][j] == '?')
                return CONTINUE;
        }
    }
    return WIN;

}

// TODO: Realese logic
enum gamestate make_move(Game *game, point move_cords, enum move_type mt)
{   
    enum gamestate move_result;
    if (mt == enter_cell) {
        move_result = handle_enter_cell(game, move_cords);
    }
    else if (mt == place_flag) {
        handle_flag(game, move_cords);
    }
    if(move_result == LOSE)
        return move_result;
    move_result = check_win(game);
    return move_result;
}

