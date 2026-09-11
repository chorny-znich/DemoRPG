#include "inventory_cell.h"
#include <SFML/Graphics/RenderTarget.hpp>

InventoryCell::InventoryCell(std::uint8_t index, sf::Vector2f pos) :
  mIndex{ index },
  mPosition{ pos }
{
  mCell.setPosition({ mPosition });
  mCell.setFillColor(CELL_COLOR);
}

void InventoryCell::render(sf::RenderTarget& target)
{
  target.draw(mCell);
  target.draw(*mSprite);
}

void InventoryCell::setCellSprite(sf::Sprite sprite)
{
  mSprite = std::make_unique<sf::Sprite>(sprite);
}

sf::Sprite* InventoryCell::getCellSprite()
{
  return mSprite.get();
}

sf::Vector2f InventoryCell::getPosition() const
{
  return mPosition;
}

std::uint8_t InventoryCell::getIndex() const
{
  return mIndex;
}