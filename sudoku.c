#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define GRID_SIZE 9

/* structure for passing data to threads */
typedef struct
{
	int row;
	int col;
	int (*grid)[GRID_SIZE];			// represents the 9x9 grid
} parameters;

/* check_row function prototype */
void* check_row(void* param);

/* check_column function prototype */
void* check_col(void* param);

/* check_square function prototype */
void* check_square(void* param);

/* sudoku function prototype */
void* sudoku(int grid[GRID_SIZE][GRID_SIZE]);

/**
 * Checks each row in the puzzle contains numbers 1-9
 * return 1 if the row is valid, 0 otherwise
 */
void* check_row(void* param)
{
	parameters* data = (parameters*) param;
	int startRow = data->row;
	int startCol = data->col;
	int status = 1;

	for (int i = startRow; i < GRID_SIZE; i++)
	{
		int tmp[10] = {0};
		for (int j = startCol; j < GRID_SIZE; j++)
		{
			int val = data->grid[i][j];
			if (tmp[val] != 0)
				status = 0;
			else
				tmp[val] = 1;
		}
		for (int j = 1; j < 10; j++)
		{
			if (tmp[j] != 1)
				printf("row[%d], missing value %d\n", i, j);
		}
	}

	if (status == 0)
		return (void*) 0;
	else
		return (void*) 1;
}

/**
 * Checks each column in the puzzle contains numbers 1-9
 * return 1 if the row is valid, 0 otherwise
 */
void* check_col(void* param)
{
	parameters* data = (parameters*) param;
	int startRow = data->row;
	int startCol = data->col;
	int status = 1;

	for (int i = startCol; i < GRID_SIZE; i++)
	{
		int tmp[10] = {0};
		for (int j = startRow; j < GRID_SIZE; j++)
		{
			int val = data->grid[j][i];
			if (tmp[val] != 0)
				status = 0;
			else
				tmp[val] = 1;
		}
		for (int h = 1; h < 10; h++)
		{
			if (tmp[h] != 1)
				printf("column[%d], missing value %d\n", i, h);
		}
	}

	if (status == 0)
		return (void*) 0;
	else
		return (void*) 1;
}

/**
 * Checks each square in the puzzle cintains numbers 1-9
 * return 1 if the row is valid, 0 otherwise
 */
void* check_square(void* param)
{
	parameters* data = (parameters*) param;
	int startRow = data->row;
	int startCol = data->col;
	int tmp[10] = {0};
	for (int i = startRow; i < (startRow+3); i++)
	{
		for (int j = startCol; j < (startCol+3); j++)
		{
			int val = data -> grid[i][j];
			if (tmp[val] != 0)
			{
				printf("puzzle[%d][%d] = %d, duplicated value\n", i, j, val);
				return (void*) 0;
			}
			else if (val < 1 || val > 9)
			{
				printf("puzzle[%d][%d] = %d, not between 1 and 9\n", i, j, val);
				return (void*) 0;
			}
			else
				tmp[val] = 1;
		}
	}
	return (void*) 1;
}

/**
 * Checks if the puzzle is valid
 * using multiple parallel threads
 */
void* sudoku(int grid[GRID_SIZE][GRID_SIZE])
{
	/* prints out the soduku grid */
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}

	/* Create the parameters for the rows check thread */
	parameters * param0 = (parameters *) malloc(sizeof(parameters));
	param0->row = 0;
	param0->col = 0;
	param0->grid = grid;

	/* Create the parameters for the columns check thread */
	parameters * param1 = (parameters *) malloc(sizeof(parameters));
	param1->row = 0;
    param1->col = 0;
    param1->grid = grid;

    /* Create the parameters for the 3x3 subgrid check threads */
	/* 1st subgrid */
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    (param2)->row = 0;
    (param2)->col = 0;
    (param2)->grid = grid;

    /* 2nd subgrid */
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    (param3)->row = 3;
    (param3)->col = 0;
    (param3)->grid = grid;

    /* 3rd subgrid */
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    (param4)->row = 6;
    (param4)->col = 0;
    (param4)->grid = grid;

    /* 4th subgrid */
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    (param5)->row = 0;
    (param5)->col = 3;
    (param5)->grid = grid;

    /* 5th subgrid */
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    (param6)->row = 3;
    (param6)->col = 3;
    (param6)->grid = grid;

    /* 6th subgrid */
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    (param7)->row = 6;
    (param7)->col = 3;
    (param7)->grid = grid;

    /* 7th subgrid */
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 0;
    param8->col = 6;
    param8->grid = grid;

    /* 8th subgrid */
	parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 3;
    param9->col = 6;
    param9->grid = grid;

    /* 9th subgrid */
    parameters * param10 = (parameters *) malloc(sizeof(parameters));
    param10->row = 6;
    param10->col = 6;
    param10->grid = grid;

	/* Create the threads
	 * Store in an array t_arr
	 */
	pthread_t t_arr[11];

	/* Create the return values for the threads
	 * store in an array r_arr
	 */
	void * r_arr[11];

	/* Initialize the threads */
	pthread_create(&t_arr[0], NULL, check_row, (void *) param0);
	pthread_create(&t_arr[1], NULL, check_col, (void *) param1);
    pthread_create(&t_arr[2], NULL, check_square, (void *) param2);
    pthread_create(&t_arr[3], NULL, check_square, (void *) param3);
    pthread_create(&t_arr[4], NULL, check_square, (void *) param4);
    pthread_create(&t_arr[5], NULL, check_square, (void *) param5);
    pthread_create(&t_arr[6], NULL, check_square, (void *) param6);
    pthread_create(&t_arr[7], NULL, check_square, (void *) param7);
    pthread_create(&t_arr[8], NULL, check_square, (void *) param8);
    pthread_create(&t_arr[9], NULL, check_square, (void *) param9);
    pthread_create(&t_arr[10], NULL, check_square, (void *) param10);

    /*Wait for all threads to finish their tasks */
    for (int h = 0; h<11; h++){
    	pthread_join(t_arr[h], &r_arr[h]);
    }

    /* Check whether the Sudoku Puzzle is valid */

    int sum = 0;
    for (int l=0; l<11; l++){
	    sum += (unsigned long)r_arr[l];  	//initiate the size of pointer and integer are the same
	}
    if (sum == 11 ){						//sum = 11 if all the return values = 1
    	printf("The Sudoku Puzzle is valid.\n");
    }else{
    	printf("The Sudoku Puzzle is NOT valid!\n");
    }
    return 0;
}

int main(){
	int puzzle1[GRID_SIZE][GRID_SIZE] = {
				{6,3,8,2,7,1,4,5,9},
				{4,2,1,8,5,9,7,3,6},
				{9,7,5,4,3,6,2,1,8},
				{3,6,9,7,2,5,1,8,4},
				{8,4,2,1,6,3,9,7,5},
				{5,1,7,9,8,4,6,2,3},
				{2,5,6,3,4,7,8,9,1},
				{1,8,3,6,9,2,5,4,7},
				{7,9,4,5,1,8,3,6,2}
	};
	int puzzle2[GRID_SIZE][GRID_SIZE] = {
				{3,4,9,5,6,7,2,1,8},
				{2,5,8,3,1,4,9,6,7},
				{1,6,7,2,8,9,4,3,5},
				{5,8,2,7,3,1,6,4,9},
				{4,9,3,6,2,8,7,5,1},
				{7,1,6,4,9,5,6,8,2},
				{8,2,4,0,5,3,1,7,6},
				{9,3,1,8,7,6,5,2,4},
				{6,7,5,1,4,2,8,9,3}
	};

	printf("Sudoku from Duong Cao");
	printf("\nPuzzle 1\n");
	sudoku(puzzle1);
	printf("\nPuzzle 2\n");
	sudoku(puzzle2);
	return 0;
}
