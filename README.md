My main propgram 'bricker.c' calls numerous functions that either update (pass-by-address)
or use variables that are defined locally within the main. 

Starts by defining a multidimensional array which contains the 5 rows of the playing board.
Then it intialises local variables, row, col, player = 1 and peice (<'X'> || <'O'>). It outputs a welcoming print statement.

If there is an command line argument, update the empty board with get_initial_board and print. 
If not, print empty board. Define a variable using board_is_full function. Program enters first while loop, which breaks if the board is full. Initialise a valid_move variable = 0.(invalid) Enter second While loop which breaks if the move is valid (= 1). Test move validity with get_move() = valid_move and get correct peice for current player. Initialise a variable that checks if the move is complete using move_complete() which passes through the updated arrays by address. 
If move is complete, the board is printed and checked for empty space, second loop is broken. 
If not, prints invalid move and does not break the loop. 

Once board is full, the first while loop will break and the winner will be printed.
