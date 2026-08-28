#include "game_world.h"
#include "money.h"
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

  switch (mState)
  {
  case GameplayState::PLAYER_ANIMATION:
    isPlayerStopMoving();
    break;
  }

  mGridController->getCursorComponent().update(dt);

  //--------------------------------------------------------------------------
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
  //---------------------------------------------------------------------------
}

/**
 * @brief 
 * @param id 
 * @param pos 
 */
void GameWorld::changeMap(uint16_t id, sf::Vector2i pos)
{
  mMapManager.loadMap(id);
  //mMapManager.getCurrentMap().initLighting({static_cast<unsigned int>(gd::GraphicsResolution.x),
  //  static_cast<unsigned int>(gd::GraphicsResolution.y)});
  mGridController->getCursorComponent().setMapSize({ static_cast<int>(mMapManager.getCurrentMap().getMapSize().x),
    static_cast<int>(mMapManager.getCurrentMap().getMapSize().y) });
  mObjectManager.createObjects(std::format("{}objects_{}.ini", gd::path::GameObjectsPath, mMapManager.getCurrentMapIndex()));
  mObjectManager.createRandomObjects(mMapManager.getCurrentMap());
  mPlayer->spawn(pos);
  mPlayer->getEnvironment()->spawn(&mMapManager.getCurrentMap());
  mPlayer->getEnvironment()->check(
    { GameWorld::instance().getPlayer().getMapPosition().x, GameWorld::instance().getPlayer().getMapPosition().y },
    GameWorld::instance().getPlayer().getRPStatsComponent()->getSecondaryStatValue(SecondaryStats::Sight));
  checkPlayerEnvironment();
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

ObjectManager& GameWorld::getObjectManager()
{
  return mObjectManager;
}

GameplayState GameWorld::getGameplayState() const
{
  return mState;
}

void GameWorld::checkPlayerEnvironment()
{
  for (const auto& direction : mPlayer->getEnvironment()->get()) 
  {
    sf::Vector2i locPosition = { static_cast<int>(direction.second[0]->mPosition.x),
      static_cast<int>(direction.second[0]->mPosition.y)};
    if (mObjectManager.isObject(mMapManager.getCurrentMap().getLocationID(locPosition)))
    {
      auto& object = mObjectManager.getObject(
        mObjectManager.isObject(mMapManager.getCurrentMap().getLocationID(locPosition)));
      if (!object->isVisible()) 
      {
        dr::Log::instance().addMessage("Maybee the hidden object here");
      }
      if (!object->isVisible() && checkVisibility(object->getVisibility())) 
      {
        dr::Log::instance().addMessage(std::format("You see {}", object->getName()));
        object->setVisibleStatus(true);
      }
    }
  }
}

/**
 * @brief Check if the player can see game's object
 * @param value - Current value of the SecondaryStats::Attention
 * @return result of the checking as a boolean value
 */
bool GameWorld::checkVisibility(int16_t value)
{
  int16_t randomValue = dr::EngineUtility::getRandomInRange(gd::DICE.x, gd::DICE.y);
  int16_t attention = mPlayer->getRPStatsComponent()->getSecondaryStatValue(SecondaryStats::Attention);
  dr::Log::instance().addMessage(std::format("Attention:{} Dice:{} Value to check:{} \n",
    attention, randomValue, value));
  return attention + randomValue >= value;
}

/**
 * @brief Check if the character stopped moving and ready to get player's input
 * @return 
 */
bool GameWorld::isPlayerStopMoving()
{
  if (!mPlayer->isAnimated())
  {
    mState = GameplayState::PLAYER_INPUT;
    mPlayer->getEnvironment()->check(
      { mPlayer->getMapPosition().x, mPlayer->getMapPosition().y },
      mPlayer->getRPStatsComponent()->getSecondaryStatValue(SecondaryStats::Sight));
    checkPlayerEnvironment();

    dr::Map& currentMap = mMapManager.getCurrentMap();
    sf::Vector2i playerTile = mPlayer->getMapPosition();
    uint16_t locID = playerTile.y * currentMap.getMapSize().x + playerTile.x;
    dr::Location& loc = currentMap.getLocation(locID);
    if (loc.isTransfer)
    {
      changeMap(loc.mapTransfer.targetMapId, loc.mapTransfer.targetTilePos);
    }
    return true;
  }
  return false;
}

/**
 * @brief Pick up various items on the map
 */
void GameWorld::pickItem()
{
  /*sf::Vector2i playerPos = mPlayer->getMapPosition();
  dr::Location& playerLoc = mMapManager.getCurrentMap().getLocation(
    playerPos.y * mMapManager.getCurrentMap().getMapSize().x + playerPos.x);
  if (mObjectManager.isObject(playerPos)) 
  {
    std::unique_ptr<dr::GameObject> object = std::move(mObjectManager.getObject(playerPos));
    if (object->getType() == GameObjectType::MONEY) {
      auto pMoneyObject = std::static_pointer_cast<Money>(object);
      auto& playerStats = mPlayer.getRPStatsComponent();
      playerStats.increaseMoney(pMoneyObject->getAmount());
      //mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You pick up ${}", pMoneyObject->getAmount()), 1);
      mObjectManager.destroyObject(playerPos);
      mRenderComponent.updateGameLayer(mObjectManager.getObjects());
    }
  }

  checkPlayerEnvironment(mPlayer.getMapPosition());
  mUpdatePlayerActions = true;
  mActionList.clear();*/
}
