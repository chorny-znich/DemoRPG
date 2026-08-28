#pragma once
#include <disreality_engine.h>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>

/**
 * @brief Manage game objects (loot)
*/
class ObjectManager
{
public:
  void createObjects(const std::string& filename);
  void createRandomObjects(dr::Map& map);
  //void createObjects(std::vector<std::unique_ptr<dr::GameObject>> objects);
  const std::unordered_map<std::uint16_t, std::unique_ptr<dr::GameObject>>& getObjects() const;
  //std::vector<std::unique_ptr<dr::GameObject>>& getObjects();
  std::unique_ptr<dr::GameObject>& getObject(std::uint16_t locID);
  bool isObject(std::uint16_t locID);
  //void destroyObject(sf::Vector2i pos);
private:
  std::unordered_map<std::uint16_t, std::unique_ptr<dr::GameObject>> mObjects;
  std::vector<std::unique_ptr<dr::GameObject>> mRandomObjects;
};