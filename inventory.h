#pragma once
#include "inventory_cell.h"
#include <vector>
#include <memory>
#include <string>
#include <disreality_engine.h>

class Inventory
{
public:
  Inventory();
  void add(std::unique_ptr<dr::GameObject> pObject);
  void show();
  size_t getSize() const;
  std::unique_ptr<dr::GameObject>& getItem(size_t index);
  void destroyItem(size_t index);
  void save();
  void setVisible(bool state);
  bool isVisible() const;
  sf::FloatRect getPanelBounds() const;
  int getClickedCellIndex(sf::FloatRect mousePos);
  std::unique_ptr<dr::GameObject> getClickedItem(sf::FloatRect mousePos);
private:
  std::vector<std::unique_ptr<dr::GameObject>> mInventory;
};

