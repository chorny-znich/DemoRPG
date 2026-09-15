#include "player_inventory_screen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

PlayerInventoryScreen::PlayerInventoryScreen()
{
  mPanel.setFillColor(PANEL_COLOR);
  mPanel.setPosition(POSITION);
  //createInventoryCells();
}

void PlayerInventoryScreen::render(sf::RenderTarget& target)
{
  if (mVisible)
  {
    target.draw(mPanel);

    for (const auto& cell : mCells) 
    {
      cell.render(target);
    }
  }
}

void PlayerInventoryScreen::show()
{
  createInventoryCells();
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
  mCells.clear();

  for (int row{ 0 }; row < INVENTORY_SIZE.y; row++)
  {
    for (int col{ 0 }; col < INVENTORY_SIZE.x; col++)
    {
      float x{ mPanel.getPosition().x + CELL_SHIFT + col * (CELL_SIZE.x + CELL_SHIFT) };
      float y{ mPanel.getPosition().y + CELL_SHIFT + row * (CELL_SIZE.y + CELL_SHIFT) };
      mCells.push_back(InventoryCell(index, { x, y }));
      index++;
    }
  }
}