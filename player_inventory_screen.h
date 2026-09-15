#pragma once
#include "inventory_cell.h"
#include "game_data.h"
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
  static inline constexpr sf::Vector2f INVENTORY_PANEL_SIZE{ INVENTORY_SIZE.x * CELL_SIZE.x + (INVENTORY_SIZE.x + 1) * CELL_SHIFT,
    INVENTORY_SIZE.y * CELL_SIZE.y + (INVENTORY_SIZE.y + 1) * CELL_SHIFT };
  static inline constexpr sf::Vector2f INVENTORY_PANEL_POSITION{ 500.f, 400.f };
  static inline constexpr sf::Color INVENTORY_PANEL_COLOR{ 139, 69, 19, 225 };

  const sf::Vector2i EQUIPMENT_SIZE{ 1, 3 };
  static inline constexpr sf::Vector2f EQUIPMENT_PANEL_SIZE{ 250.f, 400.f };
  static inline const sf::Vector2f EQUIPMENT_PANEL_POSITION{ gd::GraphicsResolution.x / 2 - EQUIPMENT_PANEL_SIZE.x / 2 + 250.f,
    gd::GraphicsResolution.y / 2 - EQUIPMENT_PANEL_SIZE.y / 2 };
  static inline constexpr sf::Color EQUIPMENT_PANEL_COLOR{ 0, 0, 0, 225 };

  sf::RectangleShape mInventoryPanel{ INVENTORY_PANEL_SIZE };
  sf::RectangleShape mEquipmentPanel{ EQUIPMENT_PANEL_SIZE };
  bool mVisible{ false };

  std::vector<InventoryCell> mInventoryCells;
  std::vector<InventoryCell> mEquipmentCells;

  void createInventoryCells();
  void createEquipmentCells();
};