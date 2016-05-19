#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <cstdlib>
using namespace std;
int const ROWS = 45;
int const COLS = 45;

typedef vector<vector< tuple<int,int,int,int> > > Vector_Matrix;
typedef vector<tuple<int,int,int,int> >Tuple_Vector;
int wrap(int n, int m) {
    return (n<0 ? (m-(-n-1)%m)-1 : n%m);
}
int getNumLivingNeighbors(int row, int col,Vector_Matrix grid) {
	int num = 0;
	for (int e = row-1; e <= row+1; e++){
		for (int i = col - 1; i <= col + 1; i++){
			if (       get<0>(grid[wrap(e, COLS)][wrap(i, ROWS)])    ){ num += 1; }
		}
	}
	if (get<0>(grid[row][col])){ num -= 1; }
	// compute the number of living neighbors of the specified cell
    return num;
}
void printMatrix(Vector_Matrix Grid){
	for (size_t i = 0; i < ROWS; i++) {
		for (size_t j = 0; j < COLS; j++) {
			printf(" %d ",get<0>(Grid[i][j]));
		}
		printf("\n" );
	}
}

Vector_Matrix initialize(){
	Vector_Matrix Grid; // initialize the vector
	///////////// initialize every sub vector and tuple inside the Matrix/////
	for (size_t i = 0; i < ROWS; i++) {
		Tuple_Vector tempVect;
		for (size_t j = 0; j < COLS; j++) {
			int num =  rand() % 3;
			tuple < int,int,int,int > tempTup (num/2,0,0,0);
			tempVect.push_back(tempTup);
		}
		Grid.push_back(tempVect);
	}
	return Grid;
	}

Vector_Matrix initialize2(){
	Vector_Matrix Grid; // initialize the vector
	///////////// initialize every sub vector and tuple inside the Matrix/////
	for (size_t i = 0; i < ROWS; i++) {
		Tuple_Vector tempVect;
		for (size_t j = 0; j < COLS; j++) {
			tuple < int,int,int,int > tempTup (0,0,0,0);
			tempVect.push_back(tempTup);
		}
		Grid.push_back(tempVect);
	}
	return Grid;
	}

Vector_Matrix update(Vector_Matrix NewGrid,Vector_Matrix Grid){
	int i = 0;
	int j = 0;
	int liveNeighbors = 0;
	for ( i = 0; i < ROWS; i++) {
		for ( j = 0; j < COLS; j++) {
			liveNeighbors = getNumLivingNeighbors(i,j,Grid);
			if (liveNeighbors > 3 || liveNeighbors < 2 ){
				get<0>(NewGrid[i][j]) = 0;
			}
			else if (liveNeighbors == 3){
				get<0>(NewGrid[i][j]) = 1;
			}
		}
	}
	return NewGrid;
}

int main(int argc, char * argv[]){
	Vector_Matrix Grid = initialize();	// printMatrix(Grid);	// printf("\n" );
	Vector_Matrix NewGrid = initialize2();	// printMatrix(NewGrid);

while(true){
	NewGrid = update(NewGrid,Grid);
	Grid = NewGrid;
	// printMatrix(Grid);
}
	return 1;
}
