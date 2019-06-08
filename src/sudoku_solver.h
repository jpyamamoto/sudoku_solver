/************************
 * Sudoku Solver (2019) *
 * Juan Pablo Yamamoto  *
 ************************/

/*
 * Defines function prototypes for the sudoku solver.
 */

#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <stdbool.h>

void init(void);
void print_board(void);
bool solve(void);
bool can_change(void);
bool valid(int *);
bool out_of_bounds(void);
bool valid_row(int *);
bool valid_column(int *);
bool valid_area(int *);

#endif
