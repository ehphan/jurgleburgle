// World Header file
class World
{
  private:
    int width;
    int height;
    Element elements[int width][int height]; //TODO: fix this
    SDL_Renderer* rend;
    int grid_px_size;

  public:
    void Init( int, int, int, SDL_Renderer*, int );
    void Cycle();
};
