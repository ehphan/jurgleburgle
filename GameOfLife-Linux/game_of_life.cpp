/* Conway's Game of Life
 *
 * The Linux version of ehphan's Game of Life.
 *
 * Author: pvphan
 *
 * Notes: 
 *  Utilizes SDL2 2.0.3 and SDL_image 2.0.0
 *  Made with the help of Lazy Foo's SDL Tutorial:
 *  http://lazyfoo.net/tutorials/SDL/index.php
 *
 */

#include <stdio.h>
#include <stdlib.h> // for rand()
#include <string>
#include <cmath>
#include <SDL2/SDL.h> // 2.0.3
#include <SDL2/SDL_image.h> // 2.0.0

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_PX_SIZE = 5;

// Start SDL and create window
bool init();

// Loads media
bool loadMedia();

// Frees up media exits SDL
void close();

// Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

// Window for rendering
SDL_Window* gWindow = NULL;

// The window's renderer
SDL_Renderer* gRenderer = NULL;

bool init() 
{
  // successful unless some SDL library init fails
  bool success = true;

  // Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize: %s\n", SDL_GetError());
    success = false;
  } else {
    // Set texture filtering to linear
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
      printf("Warning: Lienar text filtering not enabled.");
    }

    // Create window
    gWindow = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(gWindow==NULL) {
      printf("Window could not be created: %s\n", SDL_GetError());
      success = false;
    } else {
      // Create renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

      if(gRenderer == NULL) {
        printf("Renderer could not be created, SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        // Init renderer color: white
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Init PNG Loading
        int imgFlags = IMG_INIT_PNG;

        if(!(IMG_Init(imgFlags) &imgFlags)) {
          printf("SDL_image couldnot initialize, SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }
      }
    }
  }

  return success;
}

bool loadMedia()
{
  // Nothing to load in this case
  bool success = true;
  return success;
}

void close()
{
  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL
  IMG_Quit();
  SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
  // The final texture to return
  SDL_Texture* newTexture = NULL;

  // Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  if(loadedSurface == NULL) {
    printf("Unable to load image: %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture == NULL) {
      printf("Unable to create texture from %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}

int main( int argc, char* args[] )
{
  // Start up SDL and create window
  if(!init()) {
    printf("Failed to initialize!\n");
  } else {
    // Load media
    if(!loadMedia()) {
      printf("Failed to load media!\n");
    } else {

      // MAIN
      bool quit = false;

      // Event handler
      SDL_Event e;

      //TODO: Set up array
      int grid[SCREEN_WIDTH/GRID_PX_SIZE][SCREEN_HEIGHT/GRID_PX_SIZE];
      int grid_height = sizeof(grid)/sizeof(grid[0]);
      int grid_width = sizeof(grid[0]);

      printf("grid_height = %i, grid_width = %i\n", grid_height, grid_width);

      // While application is running
      while(!quit) {

        // While events in the event queue
        while(SDL_PollEvent(&e) != 0) {

          // Reconize user exit from X or press ESC key
          if(e.type == SDL_QUIT) {
            quit = true;
          } else if(e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
              case SDLK_ESCAPE:
                quit = true;
                break;
            }
          }
        }

        // GAME LOOP HERE
        
        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //TODO: Render grid
        for(int x=0; x<grid_width-1; x++) {
          for(int y=0; y<grid_height-1; y++) {
            //if(((x % 2 == 0) && (y % 2 != 0)) || ((y % 2 == 0) && (x % 2 != 0))) {
            if((rand() % 100) < 25) {
              SDL_Rect fillRect = { x*GRID_PX_SIZE, y*GRID_PX_SIZE, GRID_PX_SIZE, GRID_PX_SIZE};
              SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
              SDL_RenderFillRect(gRenderer, &fillRect);
            }
          }
        }
        
				////Render green outlined quad
				//SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
				//SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );		
				//SDL_RenderDrawRect( gRenderer, &outlineRect );
				//
				////Draw blue horizontal line
				//SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );		
				//SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

				////Draw vertical line of yellow dots
				//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
				//for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				//{
				//	SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
				//}

        // Update screen
        SDL_RenderPresent(gRenderer);
      }
    }
  }

  // clear memory
  close();

  return 0;
}
