#pragma once
#include <unordered_map>

enum class ItemList : std::uint8_t
{
  WOOD_STICK,
  RUSTY_DAGGER,
  DAGGER
};

inline std::unordered_map<ItemList, std::uint8_t> Items
{
  {ItemList::WOOD_STICK, 100},
  {ItemList::RUSTY_DAGGER, 101},
  {ItemList::DAGGER, 102},
};