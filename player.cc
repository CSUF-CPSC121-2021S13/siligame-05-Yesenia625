#include "player.h"

#include "game_element.h"
#include "opponent.h"

void Player::Draw(graphics::Image &screen) {
  // screen.DrawCircle(x_, y_, 17, 124, 77, 255);
  std::string files = "player.bmp";
  Helper(screen, files, x_, y_);
}
void PlayerProjectile::Draw(graphics::Image &screen) {
  // screen.DrawLine(x_ + 1, y_, x_ + 3, y_, 180, 136, 255, 1);
  // screen.DrawLine(x_, y_ + 1, x_ + 4, y_ + 1, 124, 77, 255, 1);
  // screen.DrawLine(x_, y_ + 2, x_ + 4, y_ + 2, 102, 31, 255, 1);
  // screen.DrawLine(x_, y_ + 3, x_ + 4, y_ + 3, 98, 0, 234, 1);
  // screen.DrawLine(x_ + 1, y_ + 4, x_ + 3, y_ + 4, 69, 39, 160, 1);
  std::string files = "p_projectile.bmp";
  Helper(screen, files, x_, y_);
}
void Player::Move(const graphics::Image &screen) {}
void PlayerProjectile::Move(const graphics::Image &screen) {
  if (!IsOutOfBounds(screen)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    check = false;
  }
}
