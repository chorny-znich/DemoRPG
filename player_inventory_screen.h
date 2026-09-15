#pragma once
#include "inventory_cell.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

/**
 * @brief User interface for player's inventory, equipment and some related stats
 */
class PlayerInventoryScreen
{
public:
  PlayerInventoryScreen();
  void update();
  void render(sf::RenderTarget& target);
  // visibility of the UI
  void show();
  void close();
  bool isVisible() const;
private:
  static inline constexpr sf::Vector2i INVENTORY_SIZE{ 10, 5 };
  static inline constexpr sf::Vector2f CELL_SIZE{ 50.f, 50.f };
  static inline constexpr float CELL_SHIFT{ 5.f };
  static inline constexpr sf::Vector2f PANEL_SIZE{ INVENTORY_SIZE.x * CELL_SIZE.x + (INVENTORY_SIZE.x + 1) * CELL_SHIFT,
    INVENTORY_SIZE.y * CELL_SIZE.y + (INVENTORY_SIZE.y + 1) * CELL_SHIFT };
  static inline constexpr sf::Vector2f POSITION{ 500.f, 400.f };
  static inline constexpr sf::Color PANEL_COLOR{ 139, 69, 19, 225 };

  sf::RectangleShape mPanel{ PANEL_SIZE };
  bool mVisible{ false };

  std::vector<InventoryCell> mCells;

  void createInventoryCells();
};