#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Example 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Example 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more tests
  cout << "Putting '5' into A1 is ";
  if (!make_move("A1", '5', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //should be invalid due to 3 in block
  cout << "Putting '3' into B8 is ";
  if (!make_move("B8", '3', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  //should be invalid due to there being a number in position
    cout << "Putting '9' into A4 is ";
  if (!make_move("A4", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  //invalid due to 4 existing in row/column
  cout << "Putting '4' into H3 is ";
  if (!make_move("H3", '4', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  cout << "=================== Example 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Example 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
    display_board(board);
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // write more tests
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "=================== Example 5 ===================\n\n";

  /* TESTS TO TIME HOW LONG EACH FUNCTION TAKES TO RUN:
  Measure time to execute solve_board for mystery1 using <chrono> library */

  /*Mystery1 time test*/
  load_board("mystery1.dat", board);

  auto start = high_resolution_clock::now();

  solve_board(board);

  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Mystery board 1 takes " << duration.count() << " microseconds\n\n";

  /*Mystery3 time test*/
  load_board("mystery3.dat", board);

  auto start2 = high_resolution_clock::now();

  solve_board(board);

  auto stop2 = high_resolution_clock::now();
  
  auto duration2 = duration_cast<microseconds>(stop2 - start2);
  cout << "Mystery board 3 takes " << duration2.count() << " microseconds\n\n";

  return 0;
}
