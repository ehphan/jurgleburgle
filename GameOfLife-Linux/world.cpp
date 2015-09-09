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

  // Create array of surrounding elements
  Element* surrounding_els;
  Element el;
  Element nel; // new Element
  Element etl, etm, etr, eml, emr, ebl, ebm, ebr; 
  int live_neighbors;

  // Create next iteration of World to generate
  World newWorld;
  newWorld.Init(height, width, 0, rend, grid_px_size);
  Element** newElements;
  newElements = newWorld.GetElements();
  
  for(int x=0; x<height; x++) {
    for(int y=0; y<width; y++) {

      printf("try %i, %i\n\n", x, y);

      live_neighbors = 0;

      el = elements[x][y];

      // calculate status of element
      if (x>0 && y>0) {
        etl = elements[x-1][y-1];
        printf("etl: "); etl.display_status();
        live_neighbors++;
      }
      if (x>0) {
        etm = elements[x-1][y];
        printf("etm: "); etm.display_status();
        live_neighbors++;
      }
      if (x>0 && y<width-1) {
        etr = elements[x-1][y+1];
        printf("etr: "); etr.display_status();
        live_neighbors++;
      }
      if (y>0) {
        eml = elements[x][y-1];
        printf("eml: "); eml.display_status();
        live_neighbors++;
      }
      if (y<width-1) {
        emr = elements[x][y+1];
        printf("emr: "); emr.display_status();
        live_neighbors++;
      }
      if (x<height-1 && y>0) {
        ebl = elements[x+1][y-1];
        printf("ebl: "); ebl.display_status();
        live_neighbors++;
      }
      if (x<height-1) {
        ebm = elements[x+1][y];
        printf("ebm: "); ebm.display_status();
        live_neighbors++;
      }
      if (x<height-1 && y<width-1) {
        ebr = elements[x+1][y+1]; 
        printf("ebr: "); ebr.display_status();
        live_neighbors++;
      }

      //printf("about to set surrounding els\n");

      //surrounding_els[0] = etl;
      //surrounding_els[1] = etm;
      //surrounding_els[2] = etr;
      //surrounding_els[3] = eml;
      //surrounding_els[4] = emr;
      //surrounding_els[5] = ebl;
      //surrounding_els[6] = ebm;
      //surrounding_els[7] = ebr;

      //printf("set surrounding els\n");

      //for (int i=0; i<8; i++) {
      //  if (surrounding_els[i].is_alive()) {
      //    printf("this neighbor is alive\n");
      //    live_neighbors++;
      //  }
      //}

      printf("[%i, %i] alive neighbors = %i\n", x, y, live_neighbors);

      // display according to status
      if (el.is_alive() && live_neighbors < 2) {
        el.dies(); // under-population
        printf("el dies (under population)\n");
      } else if (el.is_alive() && live_neighbors > 1 && live_neighbors < 4) {
        el.stays_alive(); // lives ot next generation
        printf("el stays alive\n");
      } else if (el.is_alive() && live_neighbors > 3) {
        el.dies(); // dies from overcrowding
        printf("el dies (overcrowding)\n");
      } else if (!(el.is_alive()) && live_neighbors == 3) {
        el.becomes_alive(); // comes to life!
        printf("el comes to life\n");
      }

      if (el.will_be_alive()) {
        printf("it will live: %i, %i\n", x, y);
        el.display_status();
        nel.Init(x, y, true);
        newElements[x][y] = nel;
      }
    }
  }

  // populate the new world
  for(int x=0; x<height; x++) {
    for(int y=0; y<width; y++) {
      nel = newElements[x][y];
      if (nel.is_alive()) {
        SDL_Rect fillRect;// = new SDL_Rect;
        fillRect = { nel.pos_y()*grid_px_size, nel.pos_x()*grid_px_size, grid_px_size, grid_px_size};
        SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF); // red
        SDL_RenderFillRect(rend, &fillRect);
      }
    }
  }

  // repaint
  SDL_RenderPresent(rend);
}
