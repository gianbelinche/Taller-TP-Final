

class PlayerNet;

class PlayerState {
private:
  
public:
  PlayerState();

  ~PlayerState();

  void virtual move(PlayerNet &player, int x, int y);
};
