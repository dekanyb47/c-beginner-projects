#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void get_user_input(int *rows, int *cols, int *iterations);
void game_of_life(int rows, int cols, int iterations);
void begin_main_loop(int rows, int cols, char **p_board_state, int iterations);
char **generate_random_board(int rows, int cols);
void step_board(int rows, int cols, char **p_board_state);
void print_board_state(int rows, int cols, char **p_board_state);
int get_amount_of_alive_neighbors(int rows, int cols, char **p_board_state, int r, int c);
int resolve_out_of_bound_neighbors(int coord_val, int max_coord_val);
void free_memory(int rows, char **p_board_state);

char ALIVE = '#';
char DEAD = ' ';

int main(){
    srand(time(NULL));

    int rows;
    int cols;
    int iterations;

    get_user_input(&rows, &cols, &iterations);

    game_of_life(rows, cols, iterations);
}

void get_user_input(int *p_rows, int *p_cols, int *p_iterations) {
    printf("How many rows should there be? (max 50): ");
    scanf("%d", p_rows);

    printf("How many columns should there be? (max 50): ");
    scanf("%d", p_cols);

    printf("How many iterations should be simulated?: ");
    scanf("%d", p_iterations);
    
    *p_rows = (*p_rows > 50) ? 50 : *p_rows;
    *p_cols = (*p_cols > 50) ? 50 : *p_cols;
}

void game_of_life(int rows, int cols, int iterations){
    char **p_board_state = generate_random_board(rows, cols);

    begin_main_loop(rows, cols, p_board_state, iterations);

    free_memory(rows, p_board_state);
}

char **generate_random_board(int rows, int cols){
    // allocating memory for 2d char array
    char **p_new_board = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        p_new_board[i] = malloc(cols * sizeof(char));
    }

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            bool is_alive = rand() % 2;
            p_new_board[r][c] = is_alive ? ALIVE : DEAD;
        }   
    }

    return p_new_board;
}

void begin_main_loop(int rows, int cols, char **p_board_state, int iterations){
    for (int i = 0; i < iterations; i++){
        print_board_state(rows, cols, p_board_state);
        step_board(rows, cols, p_board_state);
        sleep(1);
    }
}

void print_board_state(int rows, int cols, char **p_board_state) {
    printf("------------------\n");
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            printf("%c ", p_board_state[r][c]);
        }   
        printf("\n");
    }
    printf("------------------\n\n");
}

void step_board(int rows, int cols, char **p_board_state) {

    // initializing empty new board
    char new_board[rows][cols];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            new_board[r][c] = DEAD;
        }
    }

    // main logic
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            int neighbors_amount = get_amount_of_alive_neighbors(rows, cols, p_board_state, r, c);

            char cell = p_board_state[r][c];
            if (cell == ALIVE && (neighbors_amount < 2 || neighbors_amount > 3)) {
                new_board[r][c] = DEAD;
            }
            else if (cell == DEAD && neighbors_amount == 3) {
                new_board[r][c] = ALIVE;
            }
            else {
                new_board[r][c] = cell;
            }
        }
    }

    // copy new_board to board_state
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            p_board_state[r][c] = new_board[r][c];
        }
    }
}

int get_amount_of_alive_neighbors(int rows, int cols, char **p_board_state, int r, int c) {
    int neighbors[][2] = {
        {r + 1, c}, {r - 1, c}, {r, c + 1}, {r, c - 1},                     // next to current cell
        {r + 1, c + 1}, {r + 1, c - 1}, {r - 1, c + 1}, {r - 1, c - 1}      // diagonal to current cell
    };
    int alive_neighbors = 0;

    for (int coords_i = 0; coords_i < 8; coords_i++) {
        int nr = neighbors[coords_i][0];
        nr = resolve_out_of_bound_neighbors(nr, rows - 1);

        int nc = neighbors[coords_i][1];
        nc = resolve_out_of_bound_neighbors(nc, cols - 1);

        if (p_board_state[nr][nc] == ALIVE) {
            alive_neighbors++;
        }
    }

    return alive_neighbors;
}

int resolve_out_of_bound_neighbors(int coord_val, int max_coord_val){
    if (coord_val < 0) {
        return max_coord_val;
    }
    else if (coord_val > max_coord_val) {
        return 0;
    }
    else {
        return coord_val;
    }
}

void free_memory(int rows, char **p_board_state) {
    for (int i = 0; i < rows; i++){
        free(p_board_state[i]);
    }
    free(p_board_state);
    p_board_state = NULL;
}
