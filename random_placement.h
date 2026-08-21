#pragma once
#include <disreality_engine.h>
#include <vector>
#include <SFML/System/Vector2.hpp>

/**
 * @brief Place game objects in free random places on the map
 */
class RandomPlacement
{
public:
  RandomPlacement(dr::Map& map);
  RandomPlacement(const RandomPlacement&) = delete;
  RandomPlacement& operator=(const RandomPlacement&) = delete;
  [[nodiscard]] std::vector<sf::Vector2i> place() const;
private:
  dr::Map& mMap;
};