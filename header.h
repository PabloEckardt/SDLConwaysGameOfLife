#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <cstdlib>

int const ROWS = 66;
int const COLS = 66;
int const WINDOWX = 0;
int const WINDOWY = 0;
int const WINDOWW = 990;
int const WINDOWH = 990;

using namespace std;
//####Custom types to hold basic data structure of vector of vectors that hold tuples
//and tuple with 4 ints. The tuple has 4 places to include more information about cells
typedef vector<vector< tuple<int,int,int,int> > > Vector_Matrix;
typedef vector<tuple<int,int,int,int> >Tuple_Vector;
//Game logic functions
int wrap(int n, int m); // wrap function to calculate the right row or column
//for cells that live on the edge of the grid, regardless of size.
int getNumLivingNeighbors(int row, int col,Vector_Matrix grid) ; // count living neighbors of a cell
Vector_Matrix initialize(); // initialize with basic random seed
Vector_Matrix initialize2(); // initialize an empty grid, not necessary but useful
Vector_Matrix update(Vector_Matrix NewGrid,Vector_Matrix Grid);//Takes an old grid
                            //and generates a new grid based on the status of the cells
void printMatrix(Vector_Matrix Grid); //in case looking at the grid in ascii is needed.


//SDL2 - related functions

bool init();                //Initialize SDL2 components
bool loadMedia();           //Used to correctly load an image to the screen
void close();               // eliminate the elements created by loading SDL and the images
void DrawRectIntro(int i,int j); // Draw a rectangle for the introduction of the program.
void DrawLifeGrid(Vector_Matrix Grid); // Re-render the whole screen based on the information in a grid.
