#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class PlayerNet;
class GhostState;
class NormalState;
class MeditationState;

class PlayerState {
private:
  
public:
  PlayerState();

  ~PlayerState();

  void virtual update();

  void virtual move(PlayerNet &player, int x, int y);

public:
  static NormalState normal;
  static MeditationState meditating;
  static GhostState dead;
};
#endif // PLAYERSTATE_H
