#include "game_world.h"

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
  mGridController->getCursorComponent().update(dt);
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
