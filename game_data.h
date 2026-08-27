#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <utility>
#include <string_view>
#include <array>

namespace gd
{
  const sf::Vector2f GraphicsResolution{ 1920.f, 1080.f };

  using Position = std::pair<int16_t, int16_t>;
  using Movement = std::pair<int16_t, int16_t>;

  constexpr sf::Vector2u DICE{ 1, 12 };

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

  /**
  * @brief Map directions. Used by EnvironmentComponent. Geographical position on the map
  */
  enum class MapDirections
  {
    CURRENT,
    NORTH,
    EAST,
    SOUTH,
    WEST,
    COUNT
  };

  /**
    * @brief Normal coordinates of the MapDirections
  */
  inline const std::array<Position, 5> mCoordDirections{
    std::pair{0, 0},
    std::pair{0, -1},
    std::pair{1, 0},
    std::pair{0, 1},
    std::pair{-1, 0}
  };

  namespace path
  {
    const std::string_view PlayerInfo = "data/player.ini";
    const std::string_view GameObjectsPath = "data/objects/";
  }
}