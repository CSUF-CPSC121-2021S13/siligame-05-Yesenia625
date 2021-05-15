#include "game_element.h"

#include "cpputils/graphics/image.h"

void GameElement::Helper(graphics::Image &screen, std::string &object, int &x_,
                         int &y_) {
  graphics::Image my_sketch;
  my_sketch.Load(object);
  for (int i = 0; i < my_sketch.GetWidth(); i++) {
    for (int j = 0; j < my_sketch.GetHeight(); j++) {
      screen.SetColor(i + x_, j + y_, my_sketch.GetColor(i, j));
    }
  }
}
bool GameElement::IsOutOfBounds(const graphics::Image &screen) {
  if (x_ < 0 || y_ < 0 || x_ > screen.GetWidth() || y_ > screen.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
