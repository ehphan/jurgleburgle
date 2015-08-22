// Element Header file
class Element 
{
  private:
    bool alive;
    bool will_live;
    int x, y;

  public:
    void Init( int, int, bool );
    bool is_alive() { return alive; };
    bool will_be_alive(bool) { return will_live; };
    int pos_x() { return x; };
    int pos_y() { return y; };

};

