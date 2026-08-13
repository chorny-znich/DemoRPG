#include "game_world.h"

#include <imgui.h>
#include <imgui-SFML.h>

void GameWorld::init(sf::View& view)
{
  mPlayer = std::make_unique<Player>(sf::IntRect{ {0, 32}, {24, 32} }, dr::Textures::get("player_texture"));
  mPlayer->init();
  mGridController = std::make_unique<GridController>(view);
  changeMap(1, { 1, 1 });
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

  dr::Map& currentMap = GameWorld::instance().getMapManager().getCurrentMap();
  sf::Vector2i playerTile = GameWorld::instance().getPlayer().getMapPosition();
  uint16_t locID = playerTile.y * currentMap.getMapSize().y + playerTile.x;
  dr::Location& loc = currentMap.getLocation(locID);
  if (loc.isTransfer)
  {
    changeMap(loc.mapTransfer.targetMapId, loc.mapTransfer.targetTilePos);
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

/**
 * @brief 
 * @param id 
 * @param pos 
 */
void GameWorld::changeMap(uint16_t id, sf::Vector2i pos)
{
  mMapManager.loadMap(id);
  mGridController->getCursorComponent().setMapSize({ static_cast<int>(mMapManager.getCurrentMap().getMapSize().x),
    static_cast<int>(mMapManager.getCurrentMap().getMapSize().y) });
  mPlayer->spawn(pos);
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