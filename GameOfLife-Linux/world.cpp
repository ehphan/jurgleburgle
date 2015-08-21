// World Class file
#include "world.h"

void World::Init( int width_, int height_, int percent_alive, 
  SDL_Renderer* rend_, int grid_px_size_ ) {
  
  width = width_;
  height = height_;
  rend = rend_;
  grid_px_size = grid_px_size_;

  for(int x=0; x<width-1; x++) {
    for(int y=0; y<height-1; y++) {
      Element el;
      if((rand() % 100) < percent_alive) {
        el.Init(width, height, elements, x, y, true);
        // draw
        SDL_Rect fillRect = { x*grid_px_size, y*grid_px_size, grid_px_size, grid_px_size};
        SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF); // red
        SDL_RenderFillRect(rend, &fillRect);
      } else {
        el.Init(width, height, elements, x, y, false);
      }
      elements[x][y] = el;
    }
  }
  // repaint
  SDL_RenderPresent(rend);
}

void World::Cycle() {

  // Clear screen
  SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(rend);

  Element el;
  
  for(int x=0; x<width-1; x++) {
    for(int y=0; y<height-1; y++) {
      el = elements[x][y];

      // calculate status of element
      //
      // display according to status

    }
  }

  // repaint
  SDL_RenderPresent(rend);
}
