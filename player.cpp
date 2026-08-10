#include "player.h"

/**
 * @brief 
 * @param texture 
 * @param rect 
 */
Player::Player(sf::IntRect rect, const sf::Texture& texture) :
  dr::GameActor(rect, texture)
{
}

void Player::init()
{
	mSprite.setOrigin({ - 10.f, -4.f });
	mSprite.setScale({ 3.f, 3.f });
	mMapPosition = { 1, 1 };
}

void Player::update(float dt)
{
	mSprite.setPosition({mMapPosition.x * 128.f, mMapPosition.y * 128.f});
}

/**
 * @brief Get player's position in tile coordinates
 * @return sf::Vector 2i with player's coordinates
 */
const sf::Vector2i Player::getMapPosition() const
{
	return mMapPosition;
}
