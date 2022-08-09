#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

bool is_complete(const char board[9][9])
{
  /*loops through every row and column, checking if value is full stop*/
  for(int row = 0; row < 9; row++) {
    for(int col = 0; col < 9; col++) {
      if (board[row][col] < '1' || board[row][col] > '9') {
        return false;
      }
    }
  }
  return true;
}

bool make_move(const char position[2], const char digit, char board[9][9])
{
  /*if first coord is out of bounds A - I or 1 - 9*/
  if (position[0] < 'A' || position[0] > 'I' || !isdigit(position[1]) || position[1] == '0'){
    return false;
  }

  /*check all conditions are met (no equivalent digit on row, column, or in block), place digit in position if true*/
  if(!check_row_col(board, digit, position) || !check_block(board, digit, position) || !check_empty(board, position)){
    return false;
  }

  board[position[0] - 'A'][position[1] - '1'] = digit;
  return true;
}

bool check_row_col(const char board[9][9], const char digit, const char position[2])
{
    /*go from row 0 to 9 and column 0 - 9 using i index, checking for digit*/
    for(int i = 0; i < 9; i++){
    if (board[position[0] - 'A'][i] == digit || board[i][position[1] - '1'] == digit){
      return false;
    }
  }
  return true;
}

bool check_block(const char board[9][9], const char digit, const char position[2])
{
  /*Using modulo 3 of row and column as index, determine 3x3 block position*/
  int block_row = (position[0] - 'A') - ((position[0] - 'A') % 3);
  int block_col = (position[1] - '1') - ((position[1] - '1') % 3);

  for (int i = block_row; i < block_row + 3; i++) {
    for(int j = block_col; j < block_col + 3; j++) {
      if (board[i][j] == digit) {
        return false;
      }
    }
  }
  return true;
}

bool check_empty(const char board[9][9], const char position[2])
{
  /*checs if there is a digit placed there that is non-zero*/
  if(isdigit(board[position[0] - 'A'][position[1] - '1']) && board[position[0] - 'A'][position[1] - '1'] != '0') {
    return false;
  }
  else {
    return true;
  }
}

bool save_board(const char* filename, const char board[9][9])
{
  /*open outstream*/
  ofstream out;

  /*connect to filename in function, checking to see if file opens  correctly and returning if not*/
  out.open(filename);
  if(out.fail()) {
    return false;
  }
  assert(out);

  /*fill file with values board, outputting new line after row complete*/
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      out << board[row][col];
    }
    /*don't output newline if last row, in same fashion as easy.dat file*/
    if(row != 8)
      out << endl;
  }
  
  out.close();
  return true;
}

bool solve_board(char board[9][9])
{  
  /*Initialise counter to check number of recursive steps*/
  int counter = 0;

  /*initialise starting position, finding the position with least possible values*/
  char position[2] = {'A', '1'};
  best_position(board, position);
  
  /*run recursive helper function, allowing for counter for recursive steps*/
  if (recursive_solve(board, position, counter)) {
    cout << "\nBoard takes " << counter << " steps.\n\n";
    return true;
  }
  else {
    return false;
  }
}

bool recursive_solve(char board[9][9], char position[2], int& counter)
{
  /*success base case: if board is complete, return true to solve function*/
  if (is_complete(board)) {
    counter++;
    return true;
  }

  /*set next position to be recursed, skipping forward if the position contains an original board number*/
  char next_position[2] = {position[0], position[1]};
  
  /*Set random order of digits to test for difficulty. Doesn't affect the operation of the function*/
  char array[9] = {'1', '3', '2', '8', '7', '6', '4', '9', '5'};
  
  /*recursively solve for a possible working digit, returning back to previous position if 
  false to try next digit if true, move to next position with least options to try new digit*/
  for(int i = 0; i < 9; i++) {
    char digit = array[i];

    /*set position as zero to pass 'check_empty' test in make_move*/
    board[position[0] - 'A'][position[1] - '1'] = '.';
    
    if (make_move(position, digit, board)) {
      best_position(board, next_position);
      if (recursive_solve(board, next_position, counter)) {
      counter++;
      return true;
      }
    }
  }
  /*failure base case: delete entry to clear board for next 
  recursive pass, return to previous function stack and increment*/
  counter++;
  board[position[0] - 'A'][position[1] - '1'] = '.';
  return false;
}

void best_position(const char board[9][9], char position[2])
{
  char position_cursor[2] = {'A', '1'};
  int biggest_total_filled = 0;
  int position_total_filled = 0;

  /*loop through all positions on board, exiting when done with last row*/
  while (position_cursor[0] <= 'I')
  {
    if (check_empty(board, position_cursor)) {
      /*count number of filled positions in the row of the position, followed by filled blocks 
      in the column of the position*/
      for (int i = 0; i < 9; i++){
        if (isdigit(board[position_cursor[0] - 'A'][i])) {
          position_total_filled++;
        }
        if (isdigit(board[i][position_cursor[1] - '1'])) {
          position_total_filled++;
        }
      }
      /*set position as the position of the cursor if the number filled positions is higher
      aka less options to choose from*/
      if (position_total_filled > biggest_total_filled) {
        strcpy(position, position_cursor);
        biggest_total_filled = position_total_filled;
      }
      position_total_filled = 0;
    }
    assign_next_position(position_cursor);
  }
  return;
}

void assign_next_position(char position[2])
{ 
  /*moves to next row when column has reached '9'*/
  if (position[1] == '9') {
    position[0]++;
    position[1] = '1';
  }

  else {
    position[1]++;
  }
  return;
}