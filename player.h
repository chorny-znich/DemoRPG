#pragma once
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
class Player : public dr::GameActor
{
public:
	Player(sf::Sprite sprite);
	/*
	void init();
	sf::Sprite& getCurrentSprite();

	//void init(sf::Vector2f position);
	void update(sf::Time dt);
	void render(sf::RenderWindow& window);

	int switchAnimFrame(sf::Time dt);

	void setMovement(GameData::Movement mov);
	GameData::Movement getMovement() const;
	void setMoveDirection(GameData::MoveDirections moveDirection);
	//sf::Vector2f getCenter() const;
	void setStartPosition();
	sf::Vector2f getPosition() const;
	void setMapPosition(sf::Vector2i pos);
	const sf::Vector2i getMapPosition() const;

	void setPlayerState(PlayerState state);
	PlayerState getPlayerState() const;
	RPStats& getRPStatsComponent();

	Inventory& getInventory();
	Equipment& getEquipment();*/
	private:
		/*sf::Sprite mCurrentSprite;
		sf::Vector2f mPosition{ 256.f, 256.f };
		sf::Vector2i mMapPosition{ 2, 2 };
		GameData::Movement mMovement{ 0, 0 };
		GameData::MoveDirections mMoveDirection{ GameData::MoveDirections::NONE };
		float mMoveDestination;

		RPStats mRPStats;
		Inventory mInventory;
		Equipment mEquipment;

		float mSpeed;
		bool mMoveLeft;
		bool mMoveRight;
		bool mMoveUp;
		bool mMoveDown;

		int mAnimFrame;
		float mAnimTime;
		bool mIsAnimated;

		PlayerState mPlayerState{ PlayerState::ACT };

		void create();
		*/
};