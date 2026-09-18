#include "game_database.h"
#include "weapon.h"
#include "game_data.h"
#include <format>

/**
 * @brief Create databases (items and enimies) from ini files
 */
void GameDatabase::init()
{
  std::unordered_map<std::string, std::uint16_t> items;
  dr::IniDocument doc = dr::loadIniDocument(std::string(gd::path::ItemsInfo));
  dr::Section section = doc.getSection("general");
  items.insert({ "potion", std::stoul(section.at("Potion_amount")) });
  items.insert({ "weapon", std::stoul(section.at("Weapon_amount")) });
  items.insert({ "armor", std::stoul(section.at("Armor_amount")) });

  // Create potion objects
/*  for (size_t i{1}; i <= items.at("potion"); i++) {
    std::string sectionName = "potion_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "HEALING_POTION") {
      sf::Sprite sprite;
      sprite.setTexture(dr::Textures::get("game_objects"));
      sprite.setTextureRect({ static_cast<int>(dr::Database::getSprite("gold").x), static_cast<int>(dr::Database::getSprite("gold").y),
        static_cast<int>(GameData::TileSize.x), static_cast<int>(GameData::TileSize.y) });
      std::shared_ptr<HealingPotion> pPotion = std::make_shared<HealingPotion>(sprite);
      pPotion->setName(section.at("Name"));
      pPotion->setPrice(std::stoul(section.at("Price")));
      //mPotionDatabase.insert({i, std::move(pPotion) });
      mItemDatabase.insert({ std::stoul(section.at("Id")), std::move(pPotion) });
    }
}*/
  // Create weapon objects
  for (size_t i{ 1 }; i <= items.at("weapon"); i++) 
  {
    std::string sectionName = std::format("weapon_{}", i);
    dr::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "WEAPON")
    {
      std::uint16_t spriteID{ static_cast<uint16_t>(std::stoul(section.at("Sprite"))) };
      std::uint16_t spriteIconID{ static_cast<uint16_t>(std::stoul(section.at("Sprite_icon"))) };
      std::unique_ptr<Weapon> weapon;
      const std::string weaponType = section.at("Weapon_type");
      weapon = weaponType == "MELEE" ? std::make_unique<Weapon>(spriteID, spriteIconID, GameObjectSubType::MELEE) :
        std::make_unique<Weapon>(spriteID, spriteIconID, GameObjectSubType::RANGED);
      weapon->setName(section.at("Name"));
      weapon->setItemSpriteID(spriteID);
      weapon->setIconSpriteID(spriteIconID);
      weapon->setDamage({ static_cast<uint16_t>(std::stoul(section.at("Damage_min"))), 
        static_cast<uint16_t>(std::stoul(section.at("Damage_max"))) });
      weapon->setPrice(std::stoul(section.at("Price")));
      weapon->setWeaponType(section.at("Weapon_type") == "MELEE" ? WeaponType::MELEE : WeaponType::RANGED);
      weapon->setWeaponDistance(std::stoul(section.at("Distance")));
      mItemDatabase.insert({ std::stoul(section.at("Id")), std::move(weapon) });
    }
  }
  // Create armor objects
/*  for (size_t i{1}; i <= items.at("armor"); i++) {
    std::string sectionName = "armor_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "ARMOR") {
      sf::Sprite sprite;
      sprite.setTexture(dr::Textures::get(section.at("Texture")));
      sprite.setTextureRect({
        static_cast<int>(dr::Database::getSprite(section.at("Sprite")).x),
        static_cast<int>(dr::Database::getSprite(section.at("Sprite")).y),
        static_cast<int>(GameData::TileSize.x),
        static_cast<int>(GameData::TileSize.y)
        });
      std::shared_ptr<Armor> pArmor = std::make_shared<Armor>(GameObjectSubType::CHEST, sprite);
      pArmor->setName(section.at("Name"));
      sf::Sprite iconSprite;
      iconSprite.setTexture(dr::Textures::get(section.at("Texture_icon")));
      iconSprite.setTextureRect({
        static_cast<int>(dr::Database::getSprite(section.at("Sprite_icon")).x),
        static_cast<int>(dr::Database::getSprite(section.at("Sprite_icon")).y),
        static_cast<int>(GameData::InventoryTileSize.x),
        static_cast<int>(GameData::InventoryTileSize.y)
        });
      pArmor->setInventoryIcon(iconSprite);
      pArmor->setPrice(std::stoul(section.at("Price")));
      pArmor->setArmor(std::stoul(section.at("Armor")));
      mItemDatabase.insert({ std::stoul(section.at("Id")), std::move(pArmor) });
    }
  }*/
  // Create enemy list
/*  doc = dr::loadIniDocument(GameData::path::EnemiesInfo);
  section = doc.getSection("general");
  size_t enemyAmount = std::stoul(section.at("Enemies_amount"));

  for (size_t i{ 1 }; i <= enemyAmount; i++) {
    std::string sectionName = "enemy_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    Enemy enemy;
    enemy.getRPStatsComponent().setName(section.at("Name"));
    enemy.getRPStatsComponent().setExperienceForKill(std::stoi(section.at("Experience_for_kill")));
    enemy.getRPStatsComponent().setMaxHealth(std::stoi(section.at("Health")));
    enemy.getRPStatsComponent().setSecondaryStatValue("Attack", std::stoul(section.at("Attack")));
    enemy.getRPStatsComponent().setSecondaryStatValue("Defence", std::stoul(section.at("Defence")));
    enemy.getRPStatsComponent().setHealth(std::stoul(section.at("Health")));
    //enemy.getRPStatsComponent().setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
    enemy.getRPStatsComponent().setSecondaryStatValue("Sight", std::stoi(section.at("Sight")));
    enemy.setAnimId(section.at("Animation"));
    mEnemyDatabase.insert({ i, std::move(enemy) });
  }*/
}

/**
 * @brief Return raw pointer to the item from the database
 * @param id identifier of the item
 * @return 
 */
dr::GameObject* GameDatabase::getItem(std::uint16_t id)
{
  return mItemDatabase.at(id).get();
}
