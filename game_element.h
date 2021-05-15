#include "cpputils/graphics/image.h"
#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(const int &x, const int &y, const int width, const int &height)
      : x_(x), y_(y), width_(width), height_(height), check(true) {}
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  void SetX(const int &x) { x_ = x; }
  void SetY(const int &y) { y_ = y; }
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  virtual void Draw(graphics::Image &screen) = 0;
  void Helper(graphics::Image &screen, std::string &object, int &x_, int &y_);
  bool GetIsActive() const { return check; }
  void SetIsActive(bool insert) { check = insert; }
  virtual void Move(const graphics::Image &screen) = 0;
  bool IsOutOfBounds(const graphics::Image &screen);
  bool IntersectsWith(GameElement *my_game) {
    return !(x_ > my_game->GetX() + my_game->GetWidth() ||
             my_game->GetX() > GetX() + GetWidth() ||
             y_ > my_game->GetY() + my_game->GetHeight() ||
             my_game->GetY() > GetY() + GetHeight());
  }

 protected:
  int width_;
  int height_;
  int x_;
  int y_;
  bool check = true;
};

#endif
