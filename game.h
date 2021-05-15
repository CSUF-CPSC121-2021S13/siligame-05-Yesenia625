#include <iostream>
#include <memory>

#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    gamescreen.Initialize(width, height);
  }

  void CreateOpponents() {
    std::unique_ptr<Opponent> greenboi =
        std::make_unique<Opponent>(gamescreen.GetWidth() * 0.5, 0);
    enemy.push_back(std::move(greenboi));
  }
  void Init() {
    gamescreen.AddMouseEventListener(*this);
    gamescreen.AddAnimationEventListener(*this);
    CreateOpponents();
    player_.SetX(250);
    player_.SetY(250);
  }
  void MoveGameElements() {
    for (int j = 0; j < enemy.size(); j++) {
      if (enemy[j]->GetIsActive()) {
        enemy[j]->Move(gamescreen);
      }
    }
    for (int k = 0; k < enemyshot_.size(); k++) {
      if (enemyshot_[k]->GetIsActive()) {
        enemyshot_[k]->Move(gamescreen);
      }
    }
    for (int l = 0; l < personshot_.size(); l++) {
      if (personshot_[l]->GetIsActive()) {
        personshot_[l]->Move(gamescreen);
      }
    }
  }
  void FilterIntersections() {
    for (int j = 0; j < enemy.size(); j++) {
      if (enemy[j]->IntersectsWith(&player_)) {
        enemy[j]->SetIsActive(false);
        player_.SetIsActive(false);
        loser_ = true;
      }
    }
    for (int k = 0; k < enemyshot_.size(); k++) {
      if (enemyshot_[k]->IntersectsWith(&player_)) {
        enemyshot_[k]->SetIsActive(false);
        player_.SetIsActive(false);
        loser_ = true;
      }
    }
    for (int l = 0; l < personshot_.size(); l++) {
      for (int m = 0; m < enemy.size(); m++) {
        if (personshot_[l]->IntersectsWith(enemy[m].get())) {
          personshot_[l]->SetIsActive(false);
          enemy[m]->SetIsActive(false);
          if (player_.GetIsActive() == true) {
            winning_points_ = winning_points_ + 1;
          }
        }
      }
    }
  }

  void UpdateScreen() {
    std::string winning_score_ = "Points: ";
    winning_score_ += winning_points_;
    gamescreen.DrawRectangle(0, 0, gamescreen.GetWidth(),
                             gamescreen.GetHeight(), 255, 255, 255);
    gamescreen.DrawText(0, 570, winning_score_, 25, 190, 20, 255);
    if (loser_ == true) {
      gamescreen.DrawText(gamescreen.GetWidth() * 0, gamescreen.GetHeight() * 0,
                          "Welp You Lost LOSER!!!", 50, 190, 20, 225);
    }
    for (int j = 0; j < enemy.size(); j++) {
      if (enemy[j]->GetIsActive()) {
        enemy[j]->Draw(gamescreen);
      }
    }
    for (int k = 0; k < enemyshot_.size(); k++) {
      if (enemyshot_[k]->GetIsActive()) {
        enemyshot_[k]->Draw(gamescreen);
      }
    }
    for (int l = 0; l < personshot_.size(); l++) {
      if (personshot_[l]->GetIsActive()) {
        personshot_[l]->Draw(gamescreen);
      }
    }
    if (player_.GetIsActive() == true) {
      player_.Draw(gamescreen);
    } else if (player_.GetIsActive() == false) {
      RemoveInactive();
    }
  }
  void OnMouseEvent(const graphics::MouseEvent &event) override {
    if (event.GetX() > 0 && event.GetX() < gamescreen.GetWidth() &&
        event.GetY() > 0 && event.GetY() < gamescreen.GetHeight()) {
      player_.SetX(event.GetX() - (player_.GetWidth() * 0.5));
      player_.SetY(event.GetY() - (player_.GetHeight() * 0.5));
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> slime_ball =
          std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY());
      personshot_.push_back(std::move(slime_ball));
    }
  }
  void OnAnimationStep() override {
    if (enemy.size() == 0) {
      CreateOpponents();
    }
    MoveGameElements();
    FilterIntersections();
    UpdateScreen();
    gamescreen.Flush();
    RemoveInactive();
    LaunchProjectiles();
  }
  int GetScore() const { return winning_points_; }
  bool HasLost() const { return loser_; }
  void LaunchProjectiles() {
    for (int i = 0; i < enemy.size(); i++) {
      if (enemy[i]->LaunchProjectile() != nullptr) {
        std::unique_ptr<OpponentProjectile> slime_ball2 =
            std::make_unique<OpponentProjectile>(enemy[i]->GetX(),
                                                 enemy[i]->GetY());
        enemyshot_.push_back(std::move(slime_ball2));
      }
    }
  }
  void RemoveInactive() {
    for (int i = 0; i < enemy.size(); i++) {
      if (enemy[i]->GetIsActive() == false) {
        enemy.erase(enemy.begin());
        i = i - 1;
      }
    }
    for (int j = 0; j < enemyshot_.size(); j++) {
      if (enemyshot_[j]->GetIsActive() == false) {
        enemyshot_.erase(enemyshot_.begin());
        j = j - 1;
      }
    }
    for (int k = 0; k < personshot_.size(); k++) {
      if (personshot_[k]->GetIsActive() == false) {
        personshot_.erase(personshot_.begin());
        k = k - 1;
      }
    }
  }
  graphics::Image &GetGameScreen() { return gamescreen; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return enemy; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return enemyshot_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return personshot_;
  }
  Player &GetPlayer() { return player_; }
  void Start() { gamescreen.ShowUntilClosed(); }

 private:
  int winning_points_ = 0;
  bool loser_ = false;
  Player player_;
  graphics::Image gamescreen;
  std::vector<std::unique_ptr<Opponent>> enemy;
  std::vector<std::unique_ptr<OpponentProjectile>> enemyshot_;
  std::vector<std::unique_ptr<PlayerProjectile>> personshot_;
};

#endif
