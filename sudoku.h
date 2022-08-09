#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/*functions to write*/

/*checks to see if board is complete*/
bool is_complete(const char board[9][9]);

/*checks whether indicated move is valid, changing board if so*/
bool make_move(const char[2], const char digit, char board[9][9]);

/*make_move helper functions: checks digit not in row, column, grid, and that the position is not 
already filled*/
bool check_row_col(const char board[9][9], const char digit, const char position[2]);
bool check_block(const char board[9][9], const char digit, const char position[2]);
bool check_empty(const char board[9][9], const char position[2]);

/*save board in current state to filename provided */
bool save_board(const char* filename, const char board[9][9]);

/*breaking solve_board into 2 functions to pass a counter parameter into recursive helper function. Measures and
outputs the number of steps required to solve board*/
bool solve_board(char board[9][9]);
bool recursive_solve(char board[9][9], char position[2], int& counter);

/*helper functions:
best_position to help determine next position with least options to minimise recursion steps;
assign_next_position to correctly access next position*/
void best_position(const char board[9][9], char position[2]);
void assign_next_position(char position[2]);

#endif