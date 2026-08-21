#include "money.h"

Money::Money(uint16_t spriteID, uint16_t spriteIconID) :
  GameObject{ GameObjectType::MONEY, GameObjectSubType::NONE, spriteID, spriteIconID }
{
  setAmount();
}

void Money::setAmount(uint32_t amount)
{
  mAmount = amount;
}

size_t Money::getAmount() const
{
  return mAmount;
}