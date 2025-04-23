#include <stdio.h>
#include <stdlib.h>

#define i_type 1
#define l_left_type 2
#define l_right_type 3
#define square_type 4
#define z_right_type 5
#define z_left_type 6
#define t_type 7

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

int running = 0;

typedef struct {
    int score;
    int board[BOARD_HEIGHT][BOARD_WIDTH];
} board;

typedef struct {
    int type;
    char **size;
    int col;
    int row;
    char color;
    int (*calculate_size)(piece*);
} piece;

int calculate_size(piece* piece) {
    if(piece == NULL || piece->col == NULL || piece->row == NULL){
        return -1;
    }

    piece->size = malloc(piece->row * sizeof(char*));
    for(int i = 0; i < piece->row; i++)
        piece->size[i] = malloc(piece->col * sizeof(char));

    switch(piece->type) {
        case 4:
        case 1:
            for(int i = 0; i < piece->row; i++) {
                for(int j = 0; j < piece->col; j++) {
                    piece->size[i][j] = piece->color;
                }
            }
            break;
        case 2:    
            for(int i = 0; i < piece->row; i++) {
                for(int j = 0; j < piece->col; j++) {
                    if((i == 0 && j == 0) || (i == 1 && j == 0))
                        continue;
                    piece->size[i][j] = piece->color;
                }
            }
            break;

        case 3:    
            for(int i = 0; i < piece->row; i++) {
                for(int j = 0; j < piece->col; j++) {
                    if((i == 0 && j == 1) || (i == 1 && j == 1))
                        continue;
                    piece->size[i][j] = piece->color;
                }
            }          
            break;

        case 5:  
            for(int i = 0; i < piece->row; i++) {
                for(int j = 0; j < piece->col; j++) {
                    if((i == 0 && j == 0) || (i == 1 && j == 2))
                        continue;
                    piece->size[i][j] = piece->color;
                }
            }
            break;

        case 6:    
            for(int i = 0; i < piece->row; i++) {
                for(int j = 0; j < piece->col; j++) {
                    if((i == 0 && j == 2) || (i == 1 && j == 0))
                        continue;
                    piece->size[i][j] = piece->color;
                }
            }
            break;

        case 7:    
            for(int i = 0; i < piece->row; i++) {
                for(int j = 0; j < piece->col; j++) {
                    if((i == 0 && j == 0) || (i == 1 && j == 2))
                        continue;
                    piece->size[i][j] = piece->color;
                }
            }
            break;

    }

    return 0;
}


piece* get_piece (int type) {
    piece* piece = malloc(sizeof(piece));;

    if(type < 1 && type > 7)
        return NULL;

    piece->calculate_size = calculate_size;

    switch(type) {
        case 1:
            piece->type = i_type;
            piece->row = 4;
            piece->col = 1;
            piece->color = 'X';
        case 2:    
            piece->type = l_left_type;
            piece->row = 3;
            piece->col = 2;
            piece->color = 'O';
        case 3:    
            piece->type = l_right_type;
            piece->row = 3;
            piece->col = 2;
            piece->color = 'Z';
        case 4:    
            piece->type = square_type;
            piece->row = 2;
            piece->col = 2;
            piece->color = 'A';
        case 5:  
            piece->type = z_right_type;  
            piece->row = 3;
            piece->col = 3;
            piece->color = 'O';
        case 6:    
            piece->type = z_left_type;
            piece->row = 3;
            piece->col = 3;
            piece->color = 'Q';
        case 7:    
            piece->type = t_type;
            piece->row = 2;
            piece->col = 3;
            piece->color = 'W';
    }

    piece->calculate_size(piece);

    return piece;
}

int load_random_piece() {
    srand(time(NULL));
    int type = (rand()% 7) + 1;

    piece* piece = get_piece(type);

    if (!piece)
        return -1;


    return 0;
}

void print_game(board *board) {
    printf("SCORE: %i \n", board->score);
    for(int i = 0; i <= BOARD_WIDTH; i++){
        for(int j = 0; j <= BOARD_HEIGHT; j++) {
            if(i == 0 || i == BOARD_HEIGHT || (j == 0 || j == BOARD_WIDTH)) {
                printf('=');
                continue;
            }
            print(board->board[i][j]);
        }
    }

}

void game_loop() {
    running = 1;
    
    board* board = malloc(sizeof(board));;


    while(running) {
        print_game(board);
    }
}

int main() {
    printf("Welcome to Tetris!");  
    return 0;
}