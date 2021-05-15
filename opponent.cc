#include "opponent.h"

#include "game_element.h"

void Opponent::Draw(graphics::Image &screen) {
  // screen.DrawCircle(x_ + 100, y_ + 100, 17, 99, 221, 23);
  std::string files = "opponent.bmp";
  Helper(screen, files, x_, y_);
}
void OpponentProjectile::Draw(graphics::Image &screen) {
  // screen.DrawLine(x_ + 1, y_, x_ + 3, y_, 203, 255, 144, 1);
  // screen.DrawLine(x_, y_ + 1, x_ + 4, y_ + 1, 178, 255, 89, 1);
  // screen.DrawLine(x_, y_ + 2, x_ + 4, y_ + 2, 116, 255, 3, 1);
  // screen.DrawLine(x_, y_ + 3, x_ + 4, y_ + 3, 99, 221, 23, 1);
  // screen.DrawLine(x_ + 1, y_ + 4, x_ + 3, y_ + 4, 85, 139, 47, 1);
  std::string files = "o_projectile.bmp";
  Helper(screen, files, x_, y_);
}
std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  number_count_ += 1;
  if (number_count_ % 5 == 0) {
    std::unique_ptr<OpponentProjectile> o_projectile =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(o_projectile);
  } else {
    return nullptr;
  }
}
void Opponent::Move(const graphics::Image &screen) {
  if (!IsOutOfBounds(screen)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    check = false;
  }
}
void OpponentProjectile::Move(const graphics::Image &screen) {
  if (!IsOutOfBounds(screen)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    check = false;
  }
}
