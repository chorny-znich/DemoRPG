#include "inventory_cell.h"
#include <SFML/Graphics/RenderTarget.hpp>

InventoryCell::InventoryCell(std::uint8_t index, sf::Vector2f pos) :
  mIndex{ index },
  mPosition{ pos }
{
  mCell.setPosition({ mPosition });
  mCell.setFillColor(CELL_COLOR);
}

void InventoryCell::render(sf::RenderTarget& target) const
{
  target.draw(mCell);
  if (mSprite != nullptr)
  {
    target.draw(*mSprite);
  }
}

void InventoryCell::setCellSprite(const sf::Sprite& sprite)
{
  mSprite = std::make_unique<sf::Sprite>(sprite);
  mSprite->setPosition(mPosition);
}

sf::Sprite* InventoryCell::getCellSprite()
{
  return mSprite != nullptr ? mSprite.get() : nullptr;
}

sf::Vector2f InventoryCell::getPosition() const
{
  return mPosition;
}

std::uint8_t InventoryCell::getIndex() const
{
  return mIndex;
}