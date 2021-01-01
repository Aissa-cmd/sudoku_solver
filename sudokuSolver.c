#include <stdio.h>
#include <stdlib.h>

/*
------ SUDOKU (9x9 matix) ------
Rules:
	1- numbers in each row must be unique, each row has all the numbers from 1 to 9.
	2- numbers in each column must be unique, each column has all the numbers from 1 to 9.
	3- numbers in each square (3x3 matrix) must be unique, each square has all the numbers from 1 to 9.
*/

int backtracks = 0;

int *getNextEmptySpot(int table[][9], int rows, int cols);
int isValidNumber(int table[][9], int row, int col, int value);
int solveSudoku(int table[][9], int rows, int cols);
void display_board(int table[][9], int rows, int cols);
int all(int table[][9], int row, int col, int value);

int main(int argc, char const *argv[])
{
	int table[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9},
	};

	printf("\n");
	display_board(table, 9, 9);
	printf("\n\tSolution\n\n");
	// check if the sudoku has a solution
	// the solve sudoku returns 1 if there is a solution if not it returns 0
	if(solveSudoku(table, 9 ,9)) {
		display_board(table, 9, 9);
		printf("\nbacktracks: %d", backtracks);
	} else {
		printf("This sudoku table has no solution\n");
	}
	return 0;
}

void display_board(int table[][9], int rows, int cols) {
	int i, j;
	for(i = 0; i < rows; i++) {
		if(i % 3 == 0 && i != 0) {
			printf(" ---------------------\n");
		}
		for(j = 0; j < cols; j++) {
			if(j % 3 == 0 && j != 0) {
				printf(" |", table[i][j]);
			} if(j == 1) {
				printf(" %d", table[i][j]);
			} else {
				printf(" %d", table[i][j]);
			}
		}
		printf("\n");
	}
}

int *getNextEmptySpot(int table[][9], int rows, int cols) {
	// the returned array that contained the coordinates of the empty position
	// the first element in the x_y_coord table represent the x coordinate
	// the second element in the x_y_coord table represent the y coordinate
	int *x_y_coord = (int *) malloc(sizeof(int)*2);
	int i, j;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			// check if there is left spots in the board (empty spots represented with 0)
			if(table[i][j] == 0) {
				x_y_coord[0] = i;
				x_y_coord[1] = j;
				return x_y_coord;
			}
		}
	}
	// if there was no empty positions left in the board it returns the following:
	x_y_coord[0] = -1;
	x_y_coord[1] = -1;
	return x_y_coord;
}

int all(int table[][9], int row, int col, int value) {
	int i, x, y;
	// -1 is passed for the column or row that we want to change its values from 0, 8
	// for example we want to check if all the cells in the first row are not to equal to the passed value "value"
	// then we pass the row number in this case '0' and we pass the special value '-1' for the column
	// indecating that we want to fix the row number
	// and we want to iterate over the columns from 0 to 8
	// the same goes for checking the columns we specify the column number and pass '-1' for the row number
	for(i = 0; i < 9; i++) {
		x = (row == -1) ? i : row;
		y = (col == -1) ? i : col;
		// this if statement exits the function as soon as it finds that there a cell with
		// the same value in the same column or in the same row
		// return 0 = false
		// return 1 = true
		// basically this function answers the question are all the cells in the same column or row not equal
		// to the specified value if so it returns true (1) it not it returns false (0)
		if(table[x][y] == value) {
			return 0;
		}
	}
	return 1;
}

int isValidNumber(int table[][9], int row, int col, int value) {
	int is_row_ok, is_column_ok, top_x, top_y, i, j;
	// first test the if all the numbers in the same row are not equal to the passe value
	is_row_ok = all(table, row, -1, value);
	// if so then check the columns if not exit the function and return false (0)
	if(is_row_ok) {
		// check if all the numbers in the same column are not equal to the passed value
		is_column_ok = all(table, -1, col, value);
		// if so check the square (3x3 matrix)
		if(is_column_ok) {
			// first we need to get the x-coord and the y-coord of the square
			top_x = 3*(row/3);
			top_y = 3*(col/3);
			for(i = top_x; i < top_x+3; i++) {
				for(j = top_y; j < top_y+3; j++) {
					// check all the positions in the square
					// once it finds a position that has the number as the testing value
					// it returns false '0' and exits the function
					if(table[i][j] == value) {
						return 0;
					}
				}
			}
			return 1;
		}
	}
	return 0;
}

int solveSudoku(int table[][9], int rows, int cols) {
	int i;
	int *x_y = getNextEmptySpot(table, 9, 9);
	if(x_y[0] == -1) {
		return 1;
	}
	for(i = 1; i < 10; i++) {
		if(isValidNumber(table, x_y[0], x_y[1], i)) {
			table[x_y[0]][x_y[1]] = i;
			if(solveSudoku(table, 9, 9)) {
				return 1;
			}
			table[x_y[0]][x_y[1]] = 0;
			backtracks++;
		}
	}
	return 0;
}
