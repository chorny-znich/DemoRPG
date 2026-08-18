#pragma once
#include <cstdint>

enum class PrimaryStats : uint8_t
{
  Strength,
  Stamina, 
  Dexterity,
  Perception,
  Intellect,
  Charisma
};

enum class SecondaryStats : uint8_t
{
  Attack,
  Ranged_Attack,
  Defence,
  Attention,
  Reaction,
  Sight
};

enum class Skills : uint8_t
{
  Search,
  Athletic,
  Dodge,
  Deft_Hands
};