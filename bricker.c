#include <stdio.h> 
#include <stdlib.h>
#define BOARD_LENGTH 5
#define BOARD_SPOTS 4
#define TOTAL_SPACES 25
#define PLAYER1 'X'
#define PLAYER2 'O'

// Get print
void get_print(char (*brd_line)[9]){
    // Top Line
    char brd_start[17] = "  01234\n *******";   
    // Bottom Line of the board
    char brd_end[9] = " *******";
    // Print board
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", brd_start, brd_line[0], brd_line[1], brd_line[2], brd_line[3], brd_line[4], brd_end);
}

/*
get_initial_board: Extracts the command line args
Declaration
0 invalid | 1 valid 
*/
void get_initial_board(char **argv, char (*brd_line)[9]);

// Write a funtion to determine what line on the board we place the initial
int board_line(int x){
    int i;
    for (i =1; i <= BOARD_LENGTH; i++){
        if (x < i * BOARD_LENGTH){
            return (i - 1);
        }
    }
    return 0;
}

/*
Spot determiner: when itterating through i
This function will be able to determine particular spot on the board
*/
int get_spot(int num){
    int i, spot;
    for (i =1; i <= BOARD_LENGTH; i++){
        if (num < i*BOARD_LENGTH){
            spot = num - (i-1)*BOARD_LENGTH;
            return spot;
        }
    }
    return 0;
}

// Determines if the players input is a valid space on the board
int is_valid_input(int x){
    if (x >= 0 && x <=BOARD_SPOTS){
        return 1;
    }
    else {
        return 0;
    }
}

// Player input function
int get_move(int *row, int *col, int player){
    // Set move variable  
    printf("Player %d turn: ", player);
    scanf("%d %d", row, col);
    // RUN VALID INPUT CHECKS
    int valid_row = is_valid_input(*row);
    int valid_col = is_valid_input(*col);
    if (valid_row == 0 || valid_col == 0){
        printf("Invalid Move!\n");
        return 0;
    }
    return 1;
}

// Places the token where the player has chosen
int move_complete(int r, int c, char peice, char (*brd_line)[9] ){
    // Players token = peice
    // row, column = r , c
    if ( *(*(brd_line+r)+(c + 2)) == ' '){
        *(*(brd_line+r)+(c + 2)) = peice;
        // Place blockers
        *(*(brd_line+r)+(c + 3)) = '*';
        *(*(brd_line + r + 1)+ (c + 3)) = '*';
        *(*(brd_line+r - 1)+(c + 3)) = '*';
        *(*(brd_line+r + 1)+(c + 2)) = '*';
        *(*(brd_line+r - 1)+(c + 2)) = '*';
        *(*(brd_line+r - 1)+(c + 1)) = '*';
        *(*(brd_line+r)+(c + 1)) = '*';
        *(*(brd_line+r + 1)+(c + 1)) = '*';
        return 1;
    }
    else {
        return 0;
    }      
}

// board_is_full is a function that scans the game board to determine if thed next player can make another move
int board_is_full(char (*brd_line)[9]){
    int i, j; 
    for (i = 0; i<=BOARD_SPOTS; i++){
        for (j = 0; j <= BOARD_SPOTS; j++){
            if (*(*(brd_line+i)+(j+2)) == ' '){
                // return false
                return 0;
            }    
        }
    }
    return 1; 
}

//Player swap function
void player_swap(int *player){
    if (*player == 1){
        *player = 2;
    }
    else if (*player == 2){
        *player = 1; 
    }
}

// MAIN PORGRAM
int main(int argc,char **argv){
    // Game Board
    char brd_line[5][9] = {
        {"0*     *"}, {"1*     *"}, {"2*     *"}, {"3*     *"}, {"4*     *"}
    };
    // PLAYER MOVE DATA 
    int row, col;
    int player = 1;
    char peice; 
    // WELCOME TO THE game
    printf("Welcome to Bricker!\n");
    // If NO command line
    if (argc == 1){
        // print empty board
        get_print(brd_line);
    }
    // If there is a command line
    else if (argc == 2){
        get_initial_board(argv, brd_line);
        get_print(brd_line); 
    }
    else{
        printf("Incorrect number of command line arguments!");
    }
    /*
    Set while loop which determines if the move is able to be made
    create a function which scans through the game board
    If there are no empty spaces on the game board - Return a number for to trigger the while loop
    */
    int full = board_is_full(brd_line);
    while (full == 0){
        int valid_move = 0;        
        // Now we are in game play
        // Def function to take in user inputs 
        while (valid_move == 0){
            valid_move = get_move(&row, &col, player);          
            // set the peice 
            if (player == 1){
                peice = PLAYER1;
            }
            else{
                peice = PLAYER2;
            }       
            if (valid_move == 1){
                player = player + 1;
            }
            if (player == 3){
                player = 1;
            }
            // Do the move on the board
            int clear_move = move_complete(row, col, peice, brd_line);
            // If move is good --> print it
            if (clear_move != 0){
                get_print(brd_line);
                full = board_is_full(brd_line);
                break;
            }
            // If move is not good
            else if (valid_move != -1) {
                printf("Invalid Move!\n");
                // Need to switch player here 
                player_swap(&player);
            }
        }
    }
    // Swap player to previous player aswell 
    player_swap(&player);
    printf("Player %d Wins!\n", player);
    return 0;
}

void get_initial_board(char **argv, char (*brd_line)[9]){
 // For loop: iterates through the elements of argV
    for (int i =0; i < TOTAL_SPACES; i++){
        // Find out what line
        int line = board_line(i);       
        // Get the spot
        int spot = get_spot(i);
        // Place the symbol on the spot
        if (argv[1][i] == 'X' || argv[1][i] == 'O' || argv[1][i] == '*') {
            *(*(brd_line+line)+(spot + 2)) = argv[1][i];
        }
        // If they enter E
        else if (argv[1][i] == 'E'){
            *(*(brd_line+line)+(spot + 2)) = ' ';
        }
        // If the input is invalid
        else {
            return; 
        }
    }
    return;
}
