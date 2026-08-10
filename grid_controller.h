#pragma once
#include "game_data.h"
#include <disreality_engine.h>

/**
 * @brief 
 */
class GridController
{
public:
  GridController(sf::View& view);
  void handleInput(sf::Vector2i mouseWindowPos, sf::RenderWindow& window);

  bool checkForPlayer(const sf::Vector2i pos);
  bool checkForEnemy(const std::vector<gd::Position> enemiesPos);
  gd::MoveDirections getDirection(const sf::Vector2i pos) const;
  void setPlayerMoveStatus(bool move);
  bool isPlayerMove() const;
  void setPlayerFightStatus(bool fight);
  bool isPlayerFight() const;

  dr::CursorComponent& getCursorComponent();
private:
  dr::CursorComponent mCursorComponent;
  bool mPlayerNear{ false };
  bool mEnemyNear{ false };
  bool mPlayerMove{ false };
  bool mPlayerFight{ false };
};