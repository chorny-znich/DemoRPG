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
  setPosition({ mMapPosition.x * 128.f, mMapPosition.y * 128.f });

  create();
}

void Player::update(float dt)
{
    dr::DynamicEntity::update(dt);

    if (mMoveRight) 
    {
      move({ mSpeed * dt, 0.0f });
      if (getPosition().x > mMoveDestination) 
      {
        mMoveRight = false;
        mIsAnimated = false;
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    if (mMoveLeft)
    {
      move({ -mSpeed * dt, 0.0f });
      if (getPosition().x < mMoveDestination)
      {
        mMoveLeft = false;
        mIsAnimated = false;
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    if (mMoveUp)
    {
      move({ 0.0f, -mSpeed * dt });
      if (getPosition().y < mMoveDestination)
      {
        mMoveUp = false;
        mIsAnimated = false;
        mMapPosition = { mMapPosition.x + mMovement.first, mMapPosition.y + mMovement.second };
        mMovement = { 0, 0 };
        mAnimationComponent.setCurrentAnimation("idle");
        mAnimationComponent.setFrameDuration(0.325f);
      }
    }

    if (mMoveDown)
    {
      move({ 0.0f, mSpeed * dt });
      if (getPosition().y > mMoveDestination)
      {
        mMoveDown = false;
        mIsAnimated = false;
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
 * @param pos Player's position in tile coordinates 
 */
void Player::spawn(sf::Vector2i pos)
{
  mMapPosition = pos;
  setPosition({static_cast<float>(mMapPosition.x) * dr::SpriteDatabase::instance().getTileSize().x,
    static_cast<float>(mMapPosition.y) * dr::SpriteDatabase::instance().getTileSize().y });
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
    mMoveDestination = getPosition().x + dr::SpriteDatabase::instance().getTileSize().x;
    mMovement = { 1, 0 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_right");
    mAnimationComponent.setFrameDuration(0.125f);
    break;
  case gd::MoveDirections::LEFT:
    mMoveLeft = true;
    mMoveDestination = getPosition().x - dr::SpriteDatabase::instance().getTileSize().x;
    mMovement = { -1, 0 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_left");
    mAnimationComponent.setFrameDuration(0.125f);
    break;
  case gd::MoveDirections::UP:
    mMoveUp = true;
    mMoveDestination = getPosition().y - dr::SpriteDatabase::instance().getTileSize().y;
    mMovement = { 0, -1 };
    mIsAnimated = true;
    mAnimationComponent.setCurrentAnimation("move_up");
    mAnimationComponent.setFrameDuration(0.125f);
    break;
  case gd::MoveDirections::DOWN:
    mMoveDown = true;
    mMoveDestination = getPosition().y + dr::SpriteDatabase::instance().getTileSize().y;
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

/**
 * @brief 
 * @return 
 */
RPStatsComponent* Player::getRPStatsComponent()
{
  return &mRPStats;
}

/**
 * @brief Load player's stats from the file
 */
void Player::create()
{
  dr::IniDocument doc = dr::loadIniDocument(gd::path::PlayerInfo.data());
  dr::Section section = doc.getSection("Player");

  mRPStats.setName(section.at("Name"));
  mRPStats.setExperience(std::stoi(section.at("Experience")));
  mRPStats.setBaseMaxHealth(std::stoi(section.at("Health")));
  mRPStats.updateMaxHealth();
  mRPStats.setHealth(std::stoul(section.at("Health")));
  //spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
  mRPStats.setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
  mRPStats.setMoney({ std::stoul(section.at("Money")) });
  // set Stats
  /*section = doc.getSection("Primary stats");
  for (auto& stat : mRPStats.getPrimaryStats()) {
    stat.second = std::stoul(section.at(stat.first));
  }*/
  // Set secondary stats
  /*section = doc.getSection("Secondary stats");
  for (auto& stat : mRPStats.getSecondaryStats()) {
    stat.second = std::stoul(section.at(stat.first));
  }
  mRPStats.setBaseDefence(std::stoul(section.at("Defence")));
  mRPStats.updateDefence();*/
  // set Skills
  /*section = doc.getSection("Skills");
  for (auto& skill : mRPStats.getSkills()) {
    skill.second = std::stoul(section.at(skill.first));
  }*/
}