#include "player.h"

/**
 * @brief 
 * @param texture 
 * @param rect 
 */
Player::Player(sf::IntRect rect, const sf::Texture& texture) :
  dr::DynamicEntity(rect, texture)
{
}

void Player::init()
{
    dr::DynamicEntity::init("player_animation");
    mAnimationComponent.setCurrentAnimation("idle");
    mAnimationComponent.setFrameDuration(0.375f);
    mSprite.setTextureRect(mAnimationComponent.getCurrentRect());
	mSprite.setOrigin({ - 10.f, -4.f });
	mSprite.setScale({ 3.f, 3.f });
	mMapPosition = { 1, 1 };
}

void Player::update(float dt)
{
    dr::DynamicEntity::update(dt);
    mSprite.setTextureRect(mAnimationComponent.getCurrentRect());
	mSprite.setPosition({mMapPosition.x * 128.f, mMapPosition.y * 128.f});
}

/**
 * @brief 
 * @return 
 */
gd::Movement Player::getMovement() const
{
  return mMovement;
}

void Player::setMoveDirection(gd::MoveDirections moveDirection)
{
  mMoveDirection = moveDirection;
  switch (mMoveDirection) {
  case gd::MoveDirections::RIGHT:
    mMoveRight = true;
    //mMoveDestination = mCurrentSprite.getPosition().x + 128.f;
    mMovement = { 1, 0 };
    break;
  case gd::MoveDirections::LEFT:
    mMoveLeft = true;
    //mMoveDestination = mCurrentSprite.getPosition().x - 128.f;
    mMovement = { -1, 0 };
    break;
  case gd::MoveDirections::UP:
    mMoveUp = true;
    //mMoveDestination = mCurrentSprite.getPosition().y - 128.f;
    mMovement = { 0, -1 };
    break;
  case gd::MoveDirections::DOWN:
    mMoveDown = true;
    //mMoveDestination = mCurrentSprite.getPosition().y + 128.f;
    mMovement = { 0, 1 };
    break;
  }
}

/**
 * @brief 
 * @param pos 
 */
void Player::setMapPosition(sf::Vector2i pos)
{
	mMapPosition = pos;
}

/**
 * @brief Get player's position in tile coordinates
 * @return sf::Vector 2i with player's coordinates
 */
const sf::Vector2i Player::getMapPosition() const
{
	return mMapPosition;
}
