#include "grid_controller.h"

/**
 * @brief 
 * @param view 
 */
GridController::GridController(sf::View& view) :
  mCursorComponent(view)
{
}

/**
 * @brief 
 * @param mouseWindowPos 
 * @param window 
 */
void GridController::handleInput(sf::Vector2i mouseWindowPos, sf::RenderWindow& window)
{
  mCursorComponent.handleInput(mouseWindowPos, window);
  //mMousePosition = window.mapPixelToCoords(mouseWindowPos, window);
  //mTilePosition = { static_cast<int>(mMousePosition.x) / 128, static_cast<int>(mMousePosition.y / 128) };
  /*
  if (button == sf::Mouse::Left && mPlayerNear && !mPlayerMove && mEnemyNear) {
    mPlayerFight = true;
  }
  else if (button == sf::Mouse::Left && mPlayerNear && !mPlayerMove) {
    mPlayerMove = true;
  }*/
}

/**
 * @brief 
 * @param pos 
 * @return 
 */
bool GridController::checkForPlayer(const sf::Vector2i pos)
{ 
  sf::Vector2i tilePosition = mCursorComponent.getTilePosition();
  if (tilePosition.x == pos.x) {
    if (std::abs(tilePosition.y - pos.y) == 1) {
      mCursorComponent.changeCursorColor(sf::Color::Green);
      mPlayerNear = true;
      return true;
    }
    else if (tilePosition.y - pos.y == 0) {
      mCursorComponent.changeCursorColor(sf::Color::Black);
    }
    else {
      mCursorComponent.changeCursorColor(sf::Color::Red);
    }
  }
  else if (tilePosition.y == pos.y) {
    if (std::abs(tilePosition.x - pos.x) == 1) {
      mCursorComponent.changeCursorColor(sf::Color::Green);
      mPlayerNear = true;
      return true;
    }
    else if (tilePosition.x - pos.x == 0) {
      mCursorComponent.changeCursorColor(sf::Color::Black);
    }
    else {
      mCursorComponent.changeCursorColor(sf::Color::Red);
    }
  }
  else {
    mCursorComponent.changeCursorColor(sf::Color::Red);
  }
  mPlayerNear = false;
  return false;
}

/**
 * @brief Check if there is an enemy under the cursor
 * @param enemiesPos - std::vector with enemies positions
 * @return is any enemy under the cursor
 */
bool GridController::checkForEnemy(const std::vector<gd::Position> enemiesPos)
{ /*
  for (const auto& pos : enemiesPos) {
    if (mTilePosition.x == pos.first && mTilePosition.y == pos.second) {
      changeCursorColor(sf::Color::Magenta);
      mEnemyNear = true;
      return true;
    }
  }
  mEnemyNear = false;*/
  return false;
}

gd::MoveDirections GridController::getDirection(const sf::Vector2i& pos) const
{ 
  gd::MoveDirections result = gd::MoveDirections::NONE;
  /*if (mTilePosition.x == pos.x) {
    if (mTilePosition.y - pos.y == 1) {
      result = GameData::MoveDirections::DOWN;
    }
    else if (mTilePosition.y - pos.y == -1) {
      result = GameData::MoveDirections::UP;
    }
  }
  else if (mTilePosition.y == pos.y) {
    if (mTilePosition.x - pos.x == 1) {
      result = GameData::MoveDirections::RIGHT;
    }
    else if (mTilePosition.x - pos.x == -1) {
      result = GameData::MoveDirections::LEFT;
    }
  }*/
  return result;
}

void GridController::setPlayerMoveStatus(bool move)
{
  mPlayerMove = move;
}

bool GridController::isPlayerMove() const
{
  return mPlayerMove;
}

/**
 * @brief set state if the player fight with the enemy or not
 * @param fight - player fight with the enemy or not
 */
void GridController::setPlayerFightStatus(bool fight)
{
  mPlayerFight = fight;
}

/**
 * @brief if the player begin the battle with the enemy
 * @return player begin the battle with the enemy or not
 */
bool GridController::isPlayerFight() const
{
  return mPlayerFight;
}

dr::CursorComponent& GridController::getCursorComponent()
{
  return mCursorComponent;
}
