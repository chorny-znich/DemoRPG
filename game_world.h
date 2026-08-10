#pragma once
#include "player.h"
#include "grid_controller.h"
#include <disreality_engine.h>
#include <SFML/Graphics/View.hpp>
#include <memory>

/**
 * @brief 
 */
class GameWorld
{
private:
	GameWorld() = default;
public:
	GameWorld(const GameWorld&) = delete;
	GameWorld& operator=(const GameWorld&) = delete;
	static GameWorld& instance()
	{
		static GameWorld world;
		return world;
	}

	void init(sf::View& view);
	void update(float dt);

	dr::MapManager& getMapManager();
	Player& getPlayer();
	GridController& getGridController();
private:
	enum class GameplayState
	{
		START,
		PLAYER_INPUT,
		PLAYER_PROCESS,
		PLAYER_ANIMATION,
		ENEMY_PROCESS,
		ENEMY_ANIMATION,
		GAME_OVER
	};
	GameplayState mState{ GameplayState::START };

	dr::MapManager mMapManager;
	std::unique_ptr<Player> mPlayer{};
	std::unique_ptr<GridController> mGridController{};
};