#pragma once
#include <disreality_engine.h>

/**
 * @brief Weapon types for close and distance combat
 */
enum class WeaponType 
{
  MELEE,
  RANGED
};

class Weapon : public dr::GameObject
{
public:
  Weapon(uint16_t spriteID, uint16_t spriteIconID, GameObjectSubType type);
  ~Weapon() override = default ;
  void setDamage(sf::Vector2i dmg);
  sf::Vector2i getDamage() const;
  void setWeaponType(WeaponType type);
  WeaponType getWeaponType() const;
  void setWeaponDistance(uint8_t distance);
  uint8_t getWeaponDistance() const;
private:
  sf::Vector2i mDamage{};
  WeaponType mWeaponType;
  std::uint8_t mWeaponDistance;
};