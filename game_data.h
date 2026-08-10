#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <utility>

namespace gd
{
  /**
   * @brief Moving directions. Used by GridController
   */
  enum class MoveDirections
  {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
  };

  const sf::Vector2f GraphicsResolution{ 1920.f, 1080.f };

  using Position = std::pair<int16_t, int16_t>;
}