#include "player.h"
#include <imgui.h>
#include <imgui-SFML.h>

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
    mAnimationComponent.setFrameDuration(0.325f);
    mSprite.setTextureRect(mAnimationComponent.getCurrentRect());
	mSprite.setOrigin({ - 10.f, -4.f });
	mSprite.setScale({ 3.f, 3.f });
	mMapPosition = { 1, 1 };
  mSprite.setPosition({ mMapPosition.x * 128.f, mMapPosition.y * 128.f });
}

void Player::update(float dt)
{
    dr::DynamicEntity::update(dt);

    if (mMoveRight) 
    {
      mSprite.move({ mSpeed * dt, 0.0f });
      if (mSprite.getPosition().x > mMoveDestination) 
      {
        mMoveRight = false;
        mIsAnimated = false;
        //mPosition = mCurrentSprite.getPosition();
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    if (mMoveLeft)
    {
      mSprite.move({ -mSpeed * dt, 0.0f });
      if (mSprite.getPosition().x < mMoveDestination)
      {
        mMoveLeft = false;
        mIsAnimated = false;
        //mPosition = mCurrentSprite.getPosition();
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    if (mMoveUp)
    {
      mSprite.move({ 0.0f, -mSpeed * dt });
      if (mSprite.getPosition().y < mMoveDestination)
      {
        mMoveUp = false;
        mIsAnimated = false;
        //mPosition = mCurrentSprite.getPosition();
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    if (mMoveDown)
    {
      mSprite.move({ 0.0f, mSpeed * dt });
      if (mSprite.getPosition().y > mMoveDestination)
      {
        mMoveDown = false;
        mIsAnimated = false;
        //mPosition = mCurrentSprite.getPosition();
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    mSprite.setTextureRect(mAnimationComponent.getCurrentRect());
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
    mMoveDestination = mSprite.getPosition().x + dr::SpriteDatabase::instance().getTileSize().x;
    mMovement = { 1, 0 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_right");
    mAnimationComponent.setFrameDuration(0.125f);
    break;
  case gd::MoveDirections::LEFT:
    mMoveLeft = true;
    mMoveDestination = mSprite.getPosition().x - dr::SpriteDatabase::instance().getTileSize().x;
    mMovement = { -1, 0 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_left");
    mAnimationComponent.setFrameDuration(0.125f);
    break;
  case gd::MoveDirections::UP:
    mMoveUp = true;
    mMoveDestination = mSprite.getPosition().y - dr::SpriteDatabase::instance().getTileSize().y;
    mMovement = { 0, -1 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_up");
    mAnimationComponent.setFrameDuration(0.125f);
    break;
  case gd::MoveDirections::DOWN:
    mMoveDown = true;
    mMoveDestination = mSprite.getPosition().y + dr::SpriteDatabase::instance().getTileSize().y;
    mMovement = { 0, 1 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_down");
    mAnimationComponent.setFrameDuration(0.125f);
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

bool Player::isAnimated() const
{
  return mIsAnimated;
}
