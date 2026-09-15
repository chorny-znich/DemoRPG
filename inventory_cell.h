#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cstdint>
#include <memory>

namespace sf { class RenderTarget; }

/**
 * @brief Single cell of the player's inventory
 */
class InventoryCell
{
public:
  InventoryCell(std::uint8_t index, sf::Vector2f pos);
  void render(sf::RenderTarget& target) const;
  void setCellSprite(const sf::Sprite& sprite);
  sf::Sprite* getCellSprite();
  sf::Vector2f getPosition() const;
  std::uint8_t getIndex() const;
private:
  static inline constexpr sf::Vector2f CELL_SIZE{ 50.f, 50.f };
  static inline constexpr sf::Color CELL_COLOR{ 255, 255, 255, 175 };
  std::uint8_t mIndex{ 0 };
  sf::Vector2f mPosition{ 0.f, 0.f };
  //bool mEmpty{ true };
  sf::RectangleShape mCell{ { CELL_SIZE.x, CELL_SIZE.y } };
  std::unique_ptr<sf::Sprite> mSprite{ nullptr };
};