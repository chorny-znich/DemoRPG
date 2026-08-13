#pragma once
#include "game_data.h"
#include <disreality_engine.h>

/**
 * @brief 
 */
enum class PlayerState
{
	MOVE,
	ACT,
	WAIT,
	ATTACK,
	DEAD
};

/**
 * @brief 
 */
class Player : public dr::DynamicEntity
{
public:
	Player(sf::IntRect rect, const sf::Texture& texture);

	void init();
	void update(float dt) override;

	void spawn(sf::Vector2i pos);
	/*

	int switchAnimFrame(sf::Time dt);

	void setMovement(GameData::Movement mov);*/
	gd::Movement getMovement() const;
	void setMoveDirection(gd::MoveDirections moveDirection);/*
	//sf::Vector2f getCenter() const;
	void setStartPosition();
	sf::Vector2f getPosition() const;*/
	void setMapPosition(sf::Vector2i pos);
	const sf::Vector2i getMapPosition() const;
	bool isAnimated() const;
	/*
	void setPlayerState(PlayerState state);
	PlayerState getPlayerState() const;
	RPStats& getRPStatsComponent();

	Inventory& getInventory();
	Equipment& getEquipment();*/
	private:/*
		sf::Vector2f mPosition{ 256.f, 256.f };*/
		sf::Vector2i mMapPosition{ 2, 2 };
		gd::Movement mMovement{ 0, 0 };
		gd::MoveDirections mMoveDirection{ gd::MoveDirections::NONE };
		float mMoveDestination{};
		
		/*RPStats mRPStats;
		Inventory mInventory;
		Equipment mEquipment;
		*/
		float mSpeed{ 400.f };
		bool mMoveLeft{ false };
		bool mMoveRight{ false };
		bool mMoveUp{ false };
		bool mMoveDown{ false };
		bool mIsAnimated{ false };
		/*
		int mAnimFrame;
		float mAnimTime;
		bool mIsAnimated;

		PlayerState mPlayerState{ PlayerState::ACT };

		void create();
		*/
};