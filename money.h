#pragma once
#include <disreality_engine.h>

class Money : public dr::GameObject
{
public:
  Money(uint16_t spriteID, uint16_t spriteIconID);
  ~Money() override = default;
  void setAmount(uint32_t amount);
  size_t getAmount() const;
private:
  size_t mAmount{ 0 };
};