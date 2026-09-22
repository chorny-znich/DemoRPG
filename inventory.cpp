#include "inventory.h"

Inventory::Inventory()
{
}

void Inventory::add(std::unique_ptr<dr::GameObject> pObject)
{
  mInventory.push_back(std::move(pObject));
}

std::vector<std::unique_ptr<dr::GameObject>>& Inventory::getItems()
{
  return mInventory;
}
