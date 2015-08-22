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

  // Clear screen
  SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(rend);

  Element el;
  Element etl; 
  Element etm; 
  Element etr; 
  Element eml; 
  Element emr; 
  Element ebl; 
  Element ebm; 
  Element ebr; 
  Element* surrounding_els;

  int live_neighbors;
  
  for(int x=0; x<height; x++) {
    for(int y=0; y<width; y++) {
      el = elements[x][y];

      live_neighbors = 0;

      surrounding_els[0] = etl;
      surrounding_els[1] = etm;
      surrounding_els[2] = etr;
      surrounding_els[3] = eml;
      surrounding_els[4] = emr;
      surrounding_els[5] = ebl;
      surrounding_els[6] = ebm;
      surrounding_els[7] = ebr;

      // calculate status of element
      if (x>0 && y>0) {
        etl = elements[x-1][y-1];
      }
      if (x>0) {
        etm = elements[x-1][y];
      }
      if (x>0 && y<width-1) {
        etr = elements[x-1][y+1];
      }
      if (y>0) {
        eml = elements[x][y-1];
      }
      if (y<width-1) {
        emr = elements[x][y+1];
      }
      if (x<height-1 && y>0) {
        ebl = elements[x+1][y-1];
      }
      if (x<height-1) {
        ebm = elements[x+1][y];
      }
      if (x<height-1 && y<width-1) {
        ebr = elements[x+1][y+1];
      }

      for (int i=0; i<8; i++) {
        if (surrounding_els[i].is_alive()) {
          live_neighbors++;
        }
      }

      // display according to status
      if (el.is_alive() && live_neighbors < 2) {
        el.dies(); // under-population
        printf("it dies! (%i, %i)\n", x, y);
      } else if (el.is_alive() && live_neighbors > 1 && live_neighbors < 4) {
        el.stays_alive(); // lives ot next generation
        printf("it stays alive! (%i, %i)\n", x, y);
      } else if (el.is_alive() && live_neighbors > 3) {
        el.dies(); // overcrowding
        printf("it dies! (%i, %i)\n", x, y);
      } else if (!el.is_alive() && live_neighbors == 3) {
        el.becomes_alive();
        printf("it comes to life! (%i, %i)\n", x, y);
      } else {
        el.dies();
      }

      if (el.will_be_alive()) {
        printf("paint it! (%i, %i)\n", x, y);
        SDL_Rect fillRect = { y*grid_px_size, x*grid_px_size, grid_px_size, grid_px_size};
        SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF); // red
        SDL_RenderFillRect(rend, &fillRect);
      }
    }
  }

  // repaint
  SDL_RenderPresent(rend);
}
