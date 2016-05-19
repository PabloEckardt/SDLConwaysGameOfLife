#include "header.h"
extern int const ROWS;
extern int const COLS;
extern int const WINDOWX;
extern int const WINDOWY;
extern int const WINDOWW;
extern int const WINDOWH;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The image we will load and show on the screen
extern SDL_Surface* gOpening;

//The window renderer
extern SDL_Renderer* gRenderer;

using namespace std;

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


//Starts up SDL and creates window
bool init(){
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Conway", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWW, WINDOWH, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    return success;
}

//Loads media
bool loadMedia(){
    //Loading success flag
    bool success = true;

    //Load splash image
    gOpening = SDL_LoadBMP( "Splash.bmp" );
    if( gOpening == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "Splash.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}
//Frees media and shuts down SDL
void close(){
    //Deallocate surface
    SDL_FreeSurface( gOpening );
    gOpening = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
void DrawRectIntro(int i,int j){
	// printf("called %d   %d \n",i,j);
	SDL_Rect filledRect = {i,j,15,15};// make rectangle structure
	SDL_Rect InnerRect  ={i+2,j+2,11,11};
	SDL_SetRenderDrawColor(gRenderer,0,0,0,0xFF);
	SDL_RenderFillRect(gRenderer,&filledRect);

	SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderFillRect(gRenderer,&InnerRect);

	SDL_RenderPresent( gRenderer );
	// SDL_UpdateWindowSurface( gWindow );
}

void DrawLifeGrid(Vector_Matrix Grid){
	for (size_t i = 0; i < ROWS; i++) {
		for (size_t j = 0; j < COLS; j++) {
			SDL_Rect filledRect = {i*15,j*15,15,15};// make rectangle structure
			SDL_Rect InnerRect  ={i*15+2,j*15+2,11,11};
			if ( get<0>(Grid[i][j]) ){
				SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
				SDL_RenderFillRect(gRenderer,&InnerRect);
				SDL_SetRenderDrawColor(gRenderer,0,0,0,0xFF);
				SDL_RenderFillRect(gRenderer,&filledRect);
			}
			else{
				SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
				SDL_RenderFillRect(gRenderer,&InnerRect);
			}
		}
	}
	SDL_RenderPresent( gRenderer );
}
