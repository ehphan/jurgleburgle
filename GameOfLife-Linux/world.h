// World Header file
#include <SDL2/SDL.h> // 2.0.3
#include <SDL2/SDL_image.h> // 2.0.0

class Element;

class World
{
  private:
    int width;
    int height;
    //Element elements[int width][int height]; //TODO: fix this
    Element** elements = NULL;
    SDL_Renderer* rend = NULL;
    int grid_px_size;

  public:
    void Init( int, int, int, SDL_Renderer*, int );
    void Cycle();
};
