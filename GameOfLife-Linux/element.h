class Element 
{
private:
  bool alive;
  int x, y;

public:
  void Init( int, int, bool );
  bool is_alive() { return alive; };
  int pos_x() { return x; };
  int pos_y() { return y; };

};

