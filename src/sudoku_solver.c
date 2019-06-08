/************************
 * Sudoku Solver (2019) *
 * Juan Pablo Yamamoto  *
 ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku_solver.h"

#define BOARD_S 9
#define SQUARE_S 3
#define BOARD_BYTE_S BOARD_S * BOARD_S * sizeof(int)

//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0,0}

/*
 * Static variables. They might be used at several points in the execution
 * of the program.
 * -----------------------------------------------
 *
 * - sudoku_board[BOARD_S][BOARD_S]: Array containing the hints to solve the
 *                                   sudoku. It should be filled by the user.
 * - new_board[BOARD_S][BOARD_S]: Array only for internal use. Used to generate
 *                                the result.
 * - position: Offset from the beginning of `new_board`, holding the box whose
 *             value is being calculated.
 * - *base_ptr: Pointer to the beginning of `new_board`, used to calculate
 *              the pointer to the current box, by adding the `position`.
 */
int sudoku_board[BOARD_S][BOARD_S] = {
  {0,0,0,0,0,0,0,5,3},
  {0,0,2,7,0,9,0,4,0},
  {0,0,7,8,0,0,0,0,0},
  {0,3,0,0,0,0,0,0,6},
  {0,0,0,9,0,1,0,0,0},
  {0,8,9,0,0,2,0,0,7},
  {4,0,0,0,0,0,2,0,0},
  {1,0,0,0,6,0,9,0,0},
  {8,0,0,0,4,0,0,0,0}
};
int new_board[BOARD_S][BOARD_S];
int position = 0;
int *base_ptr = new_board[0];

/*
 * Program entrypoint.
 * Highest-level flow of execution.
 */
int main (void)
{
  init();
  print_board();
  solve();
  print_board();

  return 0;
}

/*
 * Copy the hints provided by the user through `sudoku_board` to `new_board`.
 */
void init(void)
{
  memcpy(new_board, sudoku_board, BOARD_BYTE_S);
}

/*
 * Recursive function that generates number for each box.
 */
bool solve()
{
  int *ptr = (base_ptr + position);

  if (out_of_bounds())
    return true;

  if (!can_change()) {
    position++;

    if (solve())
      return true;

    position--;
  } else {
    while (*ptr < 9) {
      (*ptr)++;
      if (valid(ptr)) {
        position++;

        if (solve())
          return true;
      }
    }

    *ptr = 0;
    position--;
  }

  return false;

}

/*
 * Check if the position is outside the bounds of the array.
 * This way it can be determined whether the result has been reached.
 */
bool out_of_bounds()
{
  return position == BOARD_S * BOARD_S;
}

/*
 * Check if the box was originally empty. Otherwise, this is a hint which
 * cannot be changed.
 */
bool can_change()
{
  return sudoku_board[position / BOARD_S][position % BOARD_S] == 0;
}

/*
 * Entrypoint to check if the current number is valid for a given box.
 */
bool valid(int *ptr)
{
  return valid_row(ptr) && valid_column(ptr) && valid_area(ptr);
}

/*
 * Check if the number does not appear twice in the current row.
 * Numbers 1 to 9 should appear exactly once.
 */
bool valid_row(int *ptr)
{
  int count = 0;
  int row = position / BOARD_S;

  for (int i=0; i<BOARD_S; i++) {
    if (new_board[row][i] == *ptr)
      count++;
  }

  return count == 1;
}

/*
 * Check if the number does not appear twice in the current column.
 * Numbers 1 to 9 should appear exactly once.
 */
bool valid_column(int *ptr)
{
  int count = 0;
  int column = position % BOARD_S;

  for (int i=0; i<BOARD_S; i++) {
    if (new_board[i][column] == *ptr)
      count++;
  }

  return count == 1;
}

/*
 * Check if the number does not appear twice in the current area.
 * An area is a 3x3 space which should contain numbers from 1 to 9 only once.
 */
bool valid_area(int *ptr)
{
  int row, column, min_row, min_column, i, j, count;
  count = 0;
  row = position / BOARD_S;
  column = position % BOARD_S;
  min_row = (row / SQUARE_S)*SQUARE_S;
  min_column = (column / SQUARE_S)*SQUARE_S;

  for (i=min_row; i<(min_row+SQUARE_S); i++) {
    for (j=min_column; j<(min_column+SQUARE_S); j++) {
      if (new_board[i][j] == *ptr)
        count++;
    }
  }

  return count == 1;
}

/*
 * Print `new_board`.
 */
void print_board()
{
  int x, y;

  for (x=0; x<BOARD_S-1; x++) {
    printf("%i", new_board[x][0]);
    for (y=1; y<BOARD_S; y++) {
      printf("|%i", new_board[x][y]);
    }

    printf("\n-----------------\n");
  }

  printf("%i", new_board[BOARD_S-1][0]);
  for (y=1; y<BOARD_S; y++) {
    printf("|%i", new_board[BOARD_S-1][y]);
  }

  printf("\n\n");
}
