
#include "header.h"
//## Constant variables and objects that need to be openly accessible ###
using namespace std;

extern int const ROWS;
extern int const COLS;
extern int const WINDOWX;
extern int const WINDOWY;
extern int const WINDOWW;
extern int const WINDOWH;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gOpening = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//###### Function prototypes: #########

  int wrap(int n, int m); // wrap function to calculate the right row or column
  //for cells that live on the edge of the grid, regardless of size.

  int getNumLivingNeighbors(int row, int col,Vector_Matrix grid) ;

  Vector_Matrix initialize(); // initialize with basic random seed
  Vector_Matrix initialize2(); // initialize an empty grid, not necessary but useful
  Vector_Matrix update(Vector_Matrix NewGrid,Vector_Matrix Grid);//Takes an old grid
                              //and generates a new grid based on the status of the cells
  bool init();                //Initialize SDL2 components
  bool loadMedia();           //Used to correctly load an image to the screen
  void close();               // eliminate the elements created by loading SDL and the images
  void DrawRectIntro(int i,int j); // Draw a rectangle for the introduction of the program.
  void DrawLifeGrid(Vector_Matrix Grid); // Re-render the whole screen based on the information in a grid.




int main(int argc, char * argv[]){
	// ########## Initialize the SDL graphic components ################
	//
	    //Start up SDL and create window
  if( !init() ){
      printf( "Failed to initialize!\n" );
  }
  else{
      //Load media
      if( !loadMedia() ){
          printf( "Failed to load media!\n" );
      }
      else{
          //Apply the image
          SDL_BlitSurface( gOpening, NULL, gScreenSurface, NULL );
					SDL_UpdateWindowSurface( gWindow );
					SDL_Delay(1000);
			}
		}
		//clear splash image
		// SDL_FillRect(gScreenSurface, NULL, 0xFFFFFF);
		// SDL_RenderPresent( gRenderer );
		// SDL_UpdateWindowSurface( gWindow );
		//Create Renderer
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
//#########Intro################

for (size_t i = 0; i < WINDOWW; i+=15) {
	for (size_t j = 0; j < WINDOWH; j+=15) {
		DrawRectIntro(j,i);
	}
}
SDL_Delay(2000);
//#########End intro ##########


// ########## END initialization of the SDL graphic components ################
//initialize the Matrix of cells
	Vector_Matrix Grid = initialize();	// printMatrix(Grid);	printf("\n" );
	Vector_Matrix NewGrid = initialize2();	// printMatrix(NewGrid);
//We need to matrices of cells to store the future one as a function of the previous one
	SDL_Event e;
	bool quit = 0;
	while(!quit){
		while( SDL_PollEvent( &e ) != 0 ){
			//Handle events on queue
			//What SDL_PollEvent does is take the most recent event from the
			//event queue and puts the data from the event into the SDL_Event we passed into the function.
				//User requests quit
				if( e.type == SDL_QUIT ){
						quit = true;
				}
		}
		//while we haven't pressed quit. Execute the logic of the program
		// SDL_FillRect(gScreenSurface, NULL, 0xFFFFFF);
		// SDL_RenderPresent( gRenderer );
		// SDL_UpdateWindowSurface( gWindow );  //this line is not necessary until the end of the frame.
		NewGrid = update(NewGrid,Grid);
		Grid = NewGrid;
		DrawLifeGrid(Grid);

		// SDL_BlitSurface( gRenderer, NULL, gScreenSurface, NULL );
		// SDL_UpdateWindowSurface( gWindow );
		}

  close(); // end program an destroy elements
	return 1;
}
