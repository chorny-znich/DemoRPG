#include "weapon.h"

Weapon::Weapon(uint16_t spriteID, uint16_t spriteIconID, GameObjectSubType type) :
  dr::GameObject(GameObjectType::WEAPON, type, spriteID, spriteIconID)
{
  setSubType(type == GameObjectSubType::MELEE ? GameObjectSubType::MELEE : GameObjectSubType::RANGED);
}

void Weapon::setDamage(sf::Vector2i dmg)
{
  mDamage = dmg;
}

sf::Vector2i Weapon::getDamage() const
{
  return mDamage;
}

void Weapon::setWeaponType(WeaponType type)
{
  mWeaponType = type;
}

WeaponType Weapon::getWeaponType() const
{
  return mWeaponType;
}

void Weapon::setWeaponDistance(uint8_t distance)
{
  mWeaponDistance = distance;
}

uint8_t Weapon::getWeaponDistance() const
{
  return mWeaponDistance;
}