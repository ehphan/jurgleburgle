// World Class file
#include "world.h"
#include "element.h"
#include <stdlib.h> // for rand()
#include <SDL2/SDL.h> // 2.0.3
#include <SDL2/SDL_image.h> // 2.0.0

void World::Init( int height_, int width_, int percent_alive, 
  SDL_Renderer* rend_, int grid_px_size_ ) {
  
  height = height_;
  width = width_;
  rend = rend_;
  grid_px_size = grid_px_size_;

  elements = new Element*[height];
  for(int i = 0; i < height; ++i) {
    elements[i] = new Element[width];
  }

  // Clear screen
  SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(rend);

  for(int x=0; x<height; x++) {
    for(int y=0; y<width; y++) {
      Element el;
      if((rand() % 100) < percent_alive) {
        el.Init(x, y, true);
        // draw
        SDL_Rect fillRect = { y*grid_px_size, x*grid_px_size, grid_px_size, grid_px_size};
        SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF); // red
        SDL_RenderFillRect(rend, &fillRect);
      } else {
        el.Init(x, y, false);
      }
      elements[x][y] = el;
    }
  }
  // repaint
  SDL_RenderPresent(rend);
}

void World::Cycle() {

  //// Clear screen
  //SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
  //SDL_RenderClear(rend);

  Element el;
  
  for(int x=0; x<height; x++) {
    for(int y=0; y<width; y++) {
      el = elements[x][y];

      // calculate status of element
      //
      // display according to status

    }
  }

  // repaint
  SDL_RenderPresent(rend);
}
