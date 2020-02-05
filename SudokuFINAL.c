#include<stdio.h>

#define SIZE 9 
 
/* This function returns 1 if the parameter is within the range of 1 to 9, inclusive.  Otherwise, the function returns 0. */ 
int isInRange(int num){
	// Conditional Statement: Check if number is within range.
	if(num>=1&&num<=9)
		return 1;
	else
		return 0;
} 
 
/* This function gets input for the 9 x 9 2D array.  
The array then represents the solution of the user to a Sudoku puzzle. 
Part of the solution for this function is call/s to isInRange() function to check that each input is valid.
 The input is taken in row-wise. */ 
void getInput(int aMatrix[][SIZE]) {  

	int row, col;    /* you are NOT allowed to declare additional variables. */ 
	
	// Row-wise loop
	for(row=0;row<9;row++)
		// Column-wise Loop
		for(col=0;col<9;col++) {
			scanf("%d", &aMatrix[row][col]);
			// If input is outside of range, set to 0
			if(isInRange(aMatrix[row][col]) == 0)
				aMatrix[row][col] = 0;
		}
}
	
/* This function displays the values in the array, which represents 1 row of values. */ 
void displayRow(int aRow[]){
	int i;
	
	for(i=0;i<9;i++){
		if(i==2||i==5) // Print last element in a section
			printf("%d   ", aRow[i]); 
		else if(i==8) // Print last element in the row
			printf("%d\n", aRow[i]);
		else // Print ordinary element
			printf("%d ", aRow[i]);
		}
}

/* This function displays the values of the 2D array, row-wise.  Showing the entries as a table. 
Part of the solution for this function is call/s to function displayRow(). */ 
void displayAll(int aMatrix[][SIZE]){
	int row;
	
	for(row=0;row<9;row++){
		// Display one row
		displayRow(aMatrix[row]);
		// After every 3 rows, print an empty line
		if(row==2 || row == 5)
			printf("\n");
	}
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int array[], int size){
	int i, bSwap=0;
	
	do{
		bSwap = 0;
		for(i=0;i<size-1;i++){
			if(array[i]>array[i+1]){
				swap(&array[i], &array[i+1]);
				bSwap = 1;
			}
		}
		size--;
	}while(bSwap);
}

/* This function returns 1 when the 1-D array aData, contains all the values 1 to 9.
 Otherwise, this function returns 0.  */ 
int checkrow(int aData[9]){
	// Declare an ideal array containing the set of valid values
	// Declare an array to copy the dataMatrix to
	int ideal[9] = {1,2,3,4,5,6,7,8,9}, copy[9];
	// Null hypothesis = same is true unless proven otherwise
	int same=1, i;
	
	// Copy the dataMatrix to temp array
	for(i=0;i<9;i++)
		copy[i] = aData[i];
	
	// Sort the temp array
	bubbleSort(copy, SIZE);
	
	// Compare the sorted temp array to the ideal valid set
	for(i=0;i<9;i++){
		if(copy[i] != ideal[i])
		// If set values are unequal, declare wrong answer.
			same = 0;
	}
	
	return same;
}
 
/* This function returns 1 when the column nColInd of the 2D array aMatrix contains all 
the values 1 to 9. Otherwise, this function returns 0. That is, this function only returns
the result of checking 1 column, where the column being checked is the one indicated by nColInd
(representing column index) */ 

int checkcol(int aMatrix[][SIZE], int nColInd){
	// Declare an ideal array containing the set of valid values
	// Declare an array to copy the dataMatrix to
	int ideal[9] = {1,2,3,4,5,6,7,8,9}, copy[9];
	// Null hypothesis = same is true unless proven otherwise
	int same=1, i;
	
	// Copy the dataMatrix to temp array
	for(i=0;i<9;i++)
		copy[i] = aMatrix[i][nColInd];
		
	// Sort the temp array
	bubbleSort(copy, SIZE);
	
	// Compare the sorted temp array to the ideal valid set
	for(i=0;i<9;i++){
		if(copy[i] != ideal[i])
		// If set values are unequal, declare wrong answer.
			same = 0;
	}
	
	return same;
}
 
/* This function returns 1 when the 3 x 3 box starting at row index nRow and the column
index nCol of the 2D array aMatrix contains all the values 1 to 9.  Otherwise, this function
returns 0.  That is, this function only returns the result of checking one of the 3 x 3 box. 
For example, if nRow is 3 and nCol is 6, this function checks the if 1 to 9 are in [3,6], [3,7],
[3,8], [4,6], [4,7], [4,8], [5,6], [5,7], [5,8]. */ 
int checkbox(int aMatrix[][SIZE], int nRow, int nCol){
	// Null hypothesis = true unless proven otherwise
	int i, j, k=0,same=1;
	// Declare an ideal array containing the valid set of values
	// Create a temp array
	int ideal[9] = {1,2,3,4,5,6,7,8,9}, copy[9];
	
	// Copy the box values to temp array
	// Get only the first three values of the row and move to next row for three rows
	for(i=nRow;i<nRow+3;i++){
		for(j=nCol;j<nCol+3;j++){
			copy[k] = aMatrix[i][j];
			k++;
		}
	}
	
	// Sort the temp array
	bubbleSort(copy, SIZE);
	
	// Compare the temp array to the ideal array
	for(i=0;i<9;i++){
		// If set values are unequal, declare wrong answer.
		if(copy[i] != ideal[i])
			same = 0;
	}
		
	return same;
}

int main(){
	// Variable Declarations
	int aMatrix[SIZE][SIZE];
	// Assume correct answer unless proven otherwise
	int solution=1;
	int i,j;
	
	// Get input
	getInput(aMatrix);
	
	// Display current sudoku solution
	displayAll(aMatrix);
	
	/* call functions checkrow(), checkcol(), checkbox() as part of your solution to determine 
	if the matrix is a correctly solved Sudoku puzzle.  Display a message Sudoku! when the matrix
	is a proper solution for Sudoku.  Otherwise, display Wrong Solution. */ 
	
	// Loop every row
	for(i=0;i<9;i++){
		// Checkrow if right or wrong
		if(checkrow(aMatrix[i])==0)
		// If wrong, declare wrong
			solution = 0;
	}
	
	// Loop every column
	for(i=0;i<9;i++){
		// Checkcol if right or wrong
		if(checkcol(aMatrix, i)==0)
		// If wrong, declare wrong
			solution = 0;
	}
	
	// Loop every first element of the box (row-wise)
	for(i=0;i<3;i++){
		// Loop every first element of the box (col-wise)
		for(j=0;j<3;j++){
			if(checkbox(aMatrix, i*3, j*3) == 0)
			// If wrong, declare wrong
				solution = 0;
		}
	}
	
	// Check solution boolean variable for solution state.
	if(solution)
		printf("Sudoku!");
	else
		printf("Wrong Solution");

	return 0;
}


