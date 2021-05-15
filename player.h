#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player() : GameElement(0, 0, 50, 50) {}
  Player(const int &x, const int &y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image &screen) override;
  void Move(const graphics::Image &screen) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : GameElement(0, 0, 5, 5) {}
  PlayerProjectile(const int &x, const int &y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image &screen) override;
  void Move(const graphics::Image &screen) override;
};

#endif
