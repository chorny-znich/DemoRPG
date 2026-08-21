#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <utility>
#include <string_view>

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
  using Movement = std::pair<int16_t, int16_t>;

  namespace path
  {
    const std::string_view PlayerInfo = "data/player.ini";
    const std::string_view GameObjectsPath = "data/objects/";
  }
}