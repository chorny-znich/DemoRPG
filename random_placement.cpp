#include "random_placement.h"
#include <algorithm>
#include <random>

RandomPlacement::RandomPlacement(dr::Map& map) :
  mMap{ map }
{
}

std::vector<sf::Vector2i> RandomPlacement::place() const
{
  std::vector<sf::Vector2i> result;
  result.reserve(mMap.getLocations().size());
  for (const auto& item : mMap.getLocations()) 
  {
    if (item.mEmpty) {
      result.push_back({ static_cast<int>(item.mPosition.x), static_cast<int>(item.mPosition.y) });
    }
  }
  static std::random_device rd;
  static std::mt19937_64 gen(rd());
  std::shuffle(result.begin(), result.end(), gen);
  return result;
}