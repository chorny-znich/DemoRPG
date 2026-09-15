#include "player_inventory_screen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

PlayerInventoryScreen::PlayerInventoryScreen()
{
  mInventoryPanel.setFillColor(INVENTORY_PANEL_COLOR);
  mInventoryPanel.setPosition(INVENTORY_PANEL_POSITION);
  mEquipmentPanel.setFillColor(EQUIPMENT_PANEL_COLOR);
  mEquipmentPanel.setPosition(EQUIPMENT_PANEL_POSITION);
  createInventoryCells();
  createEquipmentCells();
}

void PlayerInventoryScreen::render(sf::RenderTarget& target)
{
  if (mVisible)
  {
    target.draw(mInventoryPanel);
    for (const auto& cell : mInventoryCells) 
    {
      cell.render(target);
    }

    target.draw(mEquipmentPanel);
    for (const auto& cell : mEquipmentCells)
    {
      cell.render(target);
    }
  }
}

void PlayerInventoryScreen::show()
{
  mVisible = true;
}

void PlayerInventoryScreen::close()
{
  mVisible = false;
}

bool PlayerInventoryScreen::isVisible() const
{
  return mVisible;
}

void PlayerInventoryScreen::createInventoryCells()
{
  int index{ 0 };
  mInventoryCells.clear();

  for (int row{ 0 }; row < INVENTORY_SIZE.y; row++)
  {
    for (int col{ 0 }; col < INVENTORY_SIZE.x; col++)
    {
      float x{ mInventoryPanel.getPosition().x + CELL_SHIFT + col * (CELL_SIZE.x + CELL_SHIFT) };
      float y{ mInventoryPanel.getPosition().y + CELL_SHIFT + row * (CELL_SIZE.y + CELL_SHIFT) };
      mInventoryCells.push_back(InventoryCell(index, { x, y }));
      index++;
    }
  }
}

void PlayerInventoryScreen::createEquipmentCells()
{
  mEquipmentCells.push_back(InventoryCell(1, { mEquipmentPanel.getPosition().x + 100.f, 
    mEquipmentPanel.getPosition().y + 100.f }));
  mEquipmentCells.push_back(InventoryCell(2, { mEquipmentPanel.getPosition().x + CELL_SHIFT, 
    mEquipmentPanel.getPosition().y + 200.f }));
  mEquipmentCells.push_back(InventoryCell(0, { mEquipmentPanel.getPosition().x + CELL_SHIFT, 
    mEquipmentPanel.getPosition().y + CELL_SHIFT }));
}