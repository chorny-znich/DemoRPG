#include "inventory.h"

Inventory::Inventory()
{
}

 /*void Inventory::createInventoryCells()
{
  const sf::Vector2u BOUNDS = {
    static_cast<unsigned int>((INVENTORY_SIZE.x - 1) * CELL_SIZE.x + INVENTORY_SIZE.x * CELL_SHIFT),
    static_cast<unsigned int>((INVENTORY_SIZE.y - 1) * CELL_SIZE.y + INVENTORY_SIZE.y * CELL_SHIFT)
  };
 
  for (size_t i = CELL_SHIFT; i <= BOUNDS.y; i += CELL_SIZE.y + CELL_SHIFT) {
    for (size_t j = CELL_SHIFT; j <= BOUNDS.x; j += CELL_SIZE.x + CELL_SHIFT) {
      mCells.push_back(InventoryCell(index, { mPanel.getPosition().x + j, mPanel.getPosition().y + i }));
      index++;
    }
  }
 
}*/