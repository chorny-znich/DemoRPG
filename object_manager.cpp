#include "object_manager.h"
#include "money.h"
#include "random_placement.h"
#include "sprite_id.h"
#include <string>
#include <ranges>
/**
 * @brief create all game's objects from the specific file
 * @param filename path to the ini file with objects
*/
void ObjectManager::createObjects(const std::string& filename)
{
  static constexpr std::string_view RANDOM_STATE = "random";

  mObjects.clear();
  mRandomObjects.clear();
  std::unordered_map<std::string, size_t> objects;
  dr::IniDocument doc = dr::loadIniDocument(filename);
  dr::Section section = doc.getSection("general");
  objects.insert({"money", std::stoul(section.at("Money_amount"))});
  /*objects.insert({ "potion", std::stoul(section.at("Potion_amount")) });
  objects.insert({ "weapon", std::stoul(section.at("Weapon_amount")) });
  objects.insert({ "armor", std::stoul(section.at("Armor_amount")) });
  objects.insert({ "door", std::stoul(section.at("Door_amount")) });
  objects.insert({ "trap", std::stoul(section.at("Trap_amount")) });
  objects.insert({ "consumable", std::stoul(section.at("Consumable_amount")) });*/

  // Create money objects
  for (size_t i{ 1 }; i <= objects.at("money"); i++) 
  {
    bool randomPosition = false;
    std::unique_ptr<Money> money = std::make_unique<Money>(static_cast<uint16_t>(SpriteID::GOLD), 
      static_cast<uint16_t>(SpriteID::GOLD));
    std::string sectionName = std::format("money_{}", i);
    dr::Section section = doc.getSection(sectionName);
    money->setName(dr::StringManager::get("money"));
    if (section.at("Position_x") != RANDOM_STATE && section.at("Position_y") != RANDOM_STATE)
    {
      money->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    }
    else 
    {
      randomPosition = true;
    }
    money->setAmount(dr::EngineUtility::getRandomInRange(
      std::stoul(section.at("Amount_min")), std::stoul(section.at("Amount_max"))
    ));
    money->setVisibility(std::stoul(section.at("Visibility")));

    // Push object with the random placement
    if (randomPosition) 
    {
      mRandomObjects.push_back(std::move(money));
    }
    else
    {
      mObjects.push_back(std::move(money));
    }
  }
  // Create potion objects
 /* for (size_t i{1}; i <= objects.at("potion"); i++) {
    bool randomPosition = false;
    sf::Sprite sprite;
    sprite.setTexture(dr::Textures::get("game_objects"));
    sprite.setTextureRect({ static_cast<int>(dr::Database::getSprite("healing_potion").x), static_cast<int>(dr::Database::getSprite("healing_potion").y),
      static_cast<int>(GameData::TileSize.x), static_cast<int>(GameData::TileSize.y) });
    std::string sectionName = "potion_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "HEALING_POTION") {
      size_t itemId = std::stoul(section.at("Id"));
      auto object = std::static_pointer_cast<HealingPotion>(Data::getItem(itemId));
      std::shared_ptr<HealingPotion> pPotion = std::make_shared<HealingPotion>(sprite);
      pPotion->setId(itemId);
      pPotion->setName(object->getName());
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pPotion->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      sf::Sprite iconSprite;
      iconSprite.setTexture(dr::Textures::get("inventory_icons"));
      iconSprite.setTextureRect({ static_cast<int>(dr::Database::getSprite("healing_potion_icon").x),
        static_cast<int>(dr::Database::getSprite("healing_potion_icon").y),
        static_cast<int>(GameData::InventoryTileSize.x), static_cast<int>(GameData::InventoryTileSize.y) });
      pPotion->setInventoryIcon(iconSprite);
      pPotion->setPrice(object->getPrice());
      pPotion->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pPotion));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }
  // Create weapon objects
  for (size_t i{ 1 }; i <= objects.at("weapon"); i++) {
    bool randomPosition = false;
    std::string sectionName = "weapon_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "WEAPON") {
      size_t itemId = std::stoul(section.at("Id"));
      auto object = std::static_pointer_cast<Weapon>(Data::getItem(itemId));
      GameObjectSubType type = object->getSubType();
      std::shared_ptr<Weapon> pWeapon = std::make_shared<Weapon>(type, object->getSprite());
      pWeapon->setId(itemId);
      pWeapon->setName(object->getName());
      pWeapon->setInventoryIcon(object->getInventoryIcon());
      pWeapon->setDamage(object->getDamage());
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pWeapon->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pWeapon->setWeaponType(object->getWeaponType());
      pWeapon->setWeaponDistance(object->getWeaponDistance());
      pWeapon->setPrice(object->getPrice());
      pWeapon->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pWeapon));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }
  // Create armor objects
  for (size_t i{ 1 }; i <= objects.at("armor"); i++) {
    bool randomPosition = false;
    std::string sectionName = "armor_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "ARMOR") {
      size_t itemId = std::stoul(section.at("Id"));
      auto object = std::static_pointer_cast<Armor>(Data::getItem(itemId));
      GameObjectSubType type = object->getSubType();
      std::shared_ptr<Armor> pArmor = std::make_shared<Armor>(type, object->getSprite());
      pArmor->setId(itemId);
      pArmor->setName(object->getName());
      pArmor->setInventoryIcon(object->getInventoryIcon());
      pArmor->setArmor(object->getArmor());
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pArmor->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pArmor->setPrice(object->getPrice());
      pArmor->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pArmor));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }/*
  // Create door objects
  for (size_t i{ 1 }; i <= objects.at("door"); i++) {
    std::string sectionName = "door_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "DOOR") {
      std::shared_ptr<Door> pDoor = std::make_shared<Door>();
      pDoor->setName(section.at("Name"));
      pDoor->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      if (section.at("Status") == "Hidden") {
        pDoor->setImage(MapSymbols::DOOR_HIDDEN);
        pDoor->setStatus(DoorStatus::HIDDEN);
      }
      else if (section.at("Status") == "Locked") {
        pDoor->setImage(MapSymbols::DOOR_LOCKED);
        pDoor->setStatus(DoorStatus::LOCKED);
      }
      else if (section.at("Status") == "Closed") {
        pDoor->setImage(MapSymbols::DOOR_CLOSED);
        pDoor->setStatus(DoorStatus::CLOSED);
      }
      else {
        pDoor->setImage(MapSymbols::DOOR_OPEN);
        pDoor->setStatus(DoorStatus::OPEN);
      }
      pDoor->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pDoor));
    }
  }/*
  // Create trap objects
 /* for (size_t i{1}; i <= objects.at("trap"); i++) {
    bool randomPosition = false;
    std::shared_ptr<Trap> pTrap = std::make_shared<Trap>();
    std::string sectionName = "trap_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    pTrap->setName(section.at("Name"));
    if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
      pTrap->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    }
    else {
      randomPosition = true;
    }
    pTrap->setDamage({ std::stoul(section.at("Min_damage")), std::stoul(section.at("Max_damage")) });
    pTrap->setDifficulty(std::stoul(section.at("Difficulty")));
    pTrap->setVisibility(std::stoul(section.at("Visibility")));
    mObjects.push_back(std::move(pTrap));
    // Push object with the random placement
    if (randomPosition) {
      mRandomObjects.push_back(mObjects.back());
    }
  }
  // Create consumable objects
  for (size_t i{ 1 }; i <= objects.at("consumable"); i++) {
    bool randomPosition = false;
    std::string sectionName = "consumable_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "ARROW") {
      std::shared_ptr<Arrow> pArrow = std::make_shared<Arrow>();
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pArrow->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pArrow->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pArrow));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
    else if (section.at("Type") == "INGRIDIENT") {
      std::shared_ptr<Ingridient> pIngridient = std::make_shared<Ingridient>();
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pIngridient->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pIngridient->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pIngridient));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }*/
}

/**
 * @brief 
 * @param map reference to the current map
 */
void ObjectManager::createRandomObjects(dr::Map& map)
{
  RandomPlacement rp(map);
  std::vector<sf::Vector2i> positions = rp.place();
  auto iter = positions.begin();
  // Place objects with the random placement
  /*for (auto& item : mRandomObjects)
  {
    item->setPosition({ iter->x, iter->y });
    iter++;
  }*/
  for (auto&& [obj, pos] : std::views::zip(mRandomObjects, positions))
  {
    obj->setPosition({ pos.x, pos.y });
  }
  std::move(mRandomObjects.begin(), mRandomObjects.end(), std::back_inserter(mObjects));
  mRandomObjects.clear();
}
/*

void ObjectManager::createObjects(std::vector<std::unique_ptr<dr::GameObject>> objects)
{
}
*/
const std::vector<std::unique_ptr<dr::GameObject>>& ObjectManager::getObjects() const
{
  return mObjects;
}
/*
std::vector<std::unique_ptr<dr::GameObject>>& ObjectManager::getObjects()
{
  return
}

std::unique_ptr<dr::GameObject>& ObjectManager::getObject(sf::Vector2i pos)
{
  return nullptr;
}

bool ObjectManager::isObject(sf::Vector2i pos)
{
  return false;
}

void ObjectManager::destroyObject(sf::Vector2i pos)
{
}
*/