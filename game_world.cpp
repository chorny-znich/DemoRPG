#include "game_world.h"

#include <imgui.h>
#include <imgui-SFML.h>

void GameWorld::init(sf::View& view)
{
  mMapManager.loadMap(1);
  mPlayer = std::make_unique<Player>(sf::IntRect{ {0, 32}, {24, 32} }, dr::Textures::get("player_texture"));
  mPlayer->init();
  mGridController = std::make_unique<GridController>(view);
  mGridController->getCursorComponent().setMapSize({ static_cast<int>(mMapManager.getCurrentMap().getMapSize().x),
    static_cast<int>(mMapManager.getCurrentMap().getMapSize().y) });
  mGridController->getCursorComponent().init();
}

void GameWorld::update(float dt)
{
  mPlayer->update(dt);
  if (mState == GameplayState::PLAYER_ANIMATION && !mPlayer->isAnimated())
  {
    mState = GameplayState::PLAYER_INPUT;
  }

  mGridController->getCursorComponent().update(dt);

  // DEBUG SECTION
  std::string currentState{};
  switch (mState)
  {
  case GameplayState::PLAYER_INPUT:
    currentState = "player input";
    break;
  case GameplayState::PLAYER_ANIMATION:
    currentState = "player animation";
    break;
  }
  ImGui::Begin("Debug window");
  ImGui::Text(currentState.c_str());
  ImGui::End();
  //
}

bool GameWorld::isLocationPassable()
{
  return mMapManager.getCurrentMap().getLocation(mGridController->getCursorComponent().getTileId()).mPassable;
}

/**
 * @brief 
 * @return 
 */
bool GameWorld::checkMovementPossibility()
{
  bool result = GameWorld::instance().getGridController().checkForPlayer(
    GameWorld::instance().getPlayer().getMapPosition());
  if (!GameWorld::instance().isLocationPassable())
  {
    GameWorld::instance().getGridController().getCursorComponent().changeCursorColor(sf::Color::Red);
    result = false;
  }
  return result;
}

/**
 * @brief 
 */
void GameWorld::startMovePlayer()
{
  if (isLocationPassable())
  {
    mState = GameplayState::PLAYER_ANIMATION;
    mPlayer->setMoveDirection(mGridController->getDirection(mPlayer->getMapPosition()));
    //mPlayer->setMapPosition({ mPlayer->getMapPosition().x + mPlayer->getMovement().first,
      //mPlayer->getMapPosition().y + mPlayer->getMovement().second });
    movePlayer();
  }
}

/**
 * @brief 
 */
void GameWorld::movePlayer()
{
  //mState = GameplayState::PLAYER_INPUT;
}

dr::MapManager& GameWorld::getMapManager()
{
  return mMapManager;
}

Player& GameWorld::getPlayer()
{
  return *mPlayer;
}

GridController& GameWorld::getGridController()
{
  return *mGridController;
}

GameplayState GameWorld::getGameplayState() const
{
  return mState;
}