#include "player_stats_screen.h"
#include "sprite_database.h"
#include "game_data.h"
#include <disreality_engine.h>
#include <format>

/**
 * @brief 
 */
PlayerStatsScreen::PlayerStatsScreen() :
  mPlayerSprite{ dr::Textures::get("player_texture") },
  mPlayerNameValue{ dr::TextManager::get("player_stats_screen_value") },
  mLevelText{ dr::TextManager::get("player_stats_screen_title") },
  mLevelValue{ dr::TextManager::get("player_stats_screen_value") },
  mExpText{ dr::TextManager::get("player_stats_screen_title") },
  mExpValue{ dr::TextManager::get("player_stats_screen_value") },
  mHealthText{ dr::TextManager::get("player_stats_screen_title") },
  mHealthValue{ dr::TextManager::get("player_stats_screen_value") },
  mAttackText{ dr::TextManager::get("player_stats_screen_title") },
  mAttackValue{ dr::TextManager::get("player_stats_screen_value") },
  mDamageText{ dr::TextManager::get("player_stats_screen_title") },
  mDamageValue{ dr::TextManager::get("player_stats_screen_value") },
  mDefenceText{ dr::TextManager::get("player_stats_screen_title") },
  mDefenceValue{ dr::TextManager::get("player_stats_screen_value") },
  mArmorText{ dr::TextManager::get("player_stats_screen_title") },
  mArmorValue{ dr::TextManager::get("player_stats_screen_value") },
  
  mStatsDivider{ {PANEL_SIZE.x - 100.f, 5.f} },
  mStatsTitle{ dr::TextManager::get("player_stats_screen_title") },
  mSkillsDivider{ {PANEL_SIZE.x - 100.f, 5.f} },
  mSkillsTitle{ dr::TextManager::get("player_stats_screen_title") },
  mSkillPointsText{ dr::TextManager::get("player_stats_screen_title") },
  mSkillPointsValue{ dr::TextManager::get("player_stats_screen_value") }
{
}

/**
 * @brief Initialize data
 */
void PlayerStatsScreen::init(RPStatsComponent* stats)
{
  mPlayerStats = stats;

  mPanel.setPosition({
   gd::GraphicsResolution.x / 2 - PANEL_SIZE.x / 2,
   gd::GraphicsResolution.y / 2 - PANEL_SIZE.y / 2
    });
  mPanel.setFillColor(PANEL_COLOR);
  const sf::Vector2f PANEL_POSITION = mPanel.getPosition();

  mPlayerSprite.setTextureRect({ { static_cast<int>(dr::SpriteDatabase::instance().getSpriteCoords(69).x),
    static_cast<int>(dr::SpriteDatabase::instance().getSpriteCoords(69).y)},
    {24, 32} });
  mPlayerSprite.setScale({ 3.f, 3.f });
  mPlayerSprite.setPosition({ PANEL_POSITION.x + 10.f, PANEL_POSITION.y + 20.f });

  // Setup text
  mPlayerNameValue.setPosition({ PANEL_POSITION.x + 125.f, PANEL_POSITION.y + 20.f });
  mPlayerNameValue.setString(mPlayerStats->getName());
  mLevelValue.setPosition({ PANEL_POSITION.x + 125.f, PANEL_POSITION.y + 50.f });
  mLevelValue.setString("");
  mLevelText.setPosition({ PANEL_POSITION.x + 150.f, PANEL_POSITION.y + 50.f });
  mLevelText.setString("level");
  mExpText.setPosition({ PANEL_POSITION.x + 250.f, PANEL_POSITION.y + 50.f });
  mExpText.setString("EXP ");
  mExpValue.setPosition({ PANEL_POSITION.x + 300.f, PANEL_POSITION.y + 50.f });
  mExpValue.setString("");
  mHealthText.setPosition({ PANEL_POSITION.x + 125.f, PANEL_POSITION.y + 75.f });
  mHealthText.setString("HP ");
  mHealthValue.setPosition({ PANEL_POSITION.x + 150.f, PANEL_POSITION.y + 75.f });
  mHealthValue.setString("");
  mAttackText.setPosition({ PANEL_POSITION.x + 125.f, PANEL_POSITION.y + 105.f });
  mAttackText.setString("Attack");
  mAttackValue.setPosition({ PANEL_POSITION.x + 185.f, PANEL_POSITION.y + 105.f });
  mAttackValue.setString("");
  mDamageText.setPosition({ PANEL_POSITION.x + 250.f, PANEL_POSITION.y + 105.f });
  mDamageText.setString("Damage");
  mDamageValue.setPosition({ PANEL_POSITION.x + 325.f, PANEL_POSITION.y + 105.f });
  mDamageValue.setString("");
  mDefenceText.setPosition({ PANEL_POSITION.x + 125.f, PANEL_POSITION.y + 130.f });
  mDefenceText.setString("Defence");
  mDefenceValue.setPosition({ PANEL_POSITION.x + 200.f, PANEL_POSITION.y + 130.f });
  mDefenceValue.setString("");
  mArmorText.setPosition({ PANEL_POSITION.x + 250.f, PANEL_POSITION.y + 130.f });
  mArmorText.setString("Armor");
  mArmorValue.setPosition({ PANEL_POSITION.x + 325.f, PANEL_POSITION.y + 130.f });
  mArmorValue.setString("");

  // Block with primary/secondary stats/skills
  for (const auto& [key, value] : mPrimaryStatsName)
  {
    mPrimaryStatsText.emplace(key, dr::TextManager::get("player_stats_screen_title"));
    mPrimaryStatsValue.emplace(key, dr::TextManager::get("player_stats_screen_value"));
  }

  for (const auto& [key, value] : mSecondaryStatsName)
  {
    mSecondaryStatsText.emplace(key, dr::TextManager::get("player_stats_screen_title"));
    mSecondaryStatsValue.emplace(key, dr::TextManager::get("player_stats_screen_value"));
  }

  for (const auto& [key, value] : mSkillsName)
  {
    mSkillsText.emplace(key, dr::TextManager::get("player_stats_screen_title"));
    mSkillsValue.emplace(key, dr::TextManager::get("player_stats_screen_value"));
    mSkillsPlusButtons.emplace(key, dr::ImageButton({ 64.f, 64.f }, 1, 1));
  }

  mStatsDivider.setPosition({ PANEL_POSITION.x + 45.f, PANEL_POSITION.y + 165.f });
  mStatsDivider.setFillColor(sf::Color(255, 239, 213, 200));

  mStatsTitle.setPosition({ PANEL_POSITION.x + PANEL_SIZE.x / 2 - 100.f, PANEL_POSITION.y + 172.f });
  mStatsTitle.setString("Primary/Secondary stats");

  sf::Vector2f startPosition{ PANEL_POSITION.x + 25.f, PANEL_POSITION.y + 205.f };
  const float VERT_STEP{ 25.f };
  int iteration{ 0 };

  for (auto& [stat, text] : mPrimaryStatsText)
  {
    text.setPosition({ startPosition.x, startPosition.y + iteration * VERT_STEP });
    text.setString(mPrimaryStatsName.at(stat));
    mPrimaryStatsValue.at(stat).setPosition({startPosition.x + 125.f, startPosition.y + iteration * VERT_STEP});
    iteration++;
  }
 
  iteration = 0;
  for (auto& [stat, text] : mSecondaryStatsText) 
  {
    text.setPosition({ startPosition.x + 200.f, startPosition.y + iteration * VERT_STEP });
    text.setString(mSecondaryStatsName.at(stat));
    mSecondaryStatsValue.at(stat).setPosition({ startPosition.x + 325.f, startPosition.y + iteration * VERT_STEP });
    iteration++;
  }

  mSkillsDivider.setPosition({ startPosition.x + 25.f, startPosition.y + 175.f });
  mSkillsDivider.setFillColor(sf::Color(255, 239, 213, 200));

  mSkillsTitle.setPosition({ startPosition.x + PANEL_SIZE.x / 2 - 50.f, startPosition.y + 182.f });
  mSkillsTitle.setString("Skills");

  mSkillPointsText.setPosition({ startPosition.x, startPosition.y + 210.f });
  mSkillPointsText.setString("Skill points");
  mSkillPointsValue.setPosition({ startPosition.x + 125.f, startPosition.y + 210.f });

  iteration = 0;
  for (auto& [skill, text] : mSkillsText) 
  {
    text.setPosition({ startPosition.x, startPosition.y + 245.f + iteration * VERT_STEP });
    text.setString(mSkillsName.at(skill));
    mSkillsValue.at(skill).setPosition({ startPosition.x + 125.f, startPosition.y + 245.f + iteration * VERT_STEP });
    iteration++;
  }
}

/**
 * @brief update the logic
 * @param dt - time that the single frame takes
 */
void PlayerStatsScreen::update(float dt)
{
  if (mVisible && mNeedsUpdate) 
  {
    mLevelValue.setString(std::format("{}", mPlayerStats->getLevel()));
    mExpValue.setString(std::format("{}/{}", mPlayerStats->getExperience(),
      mPlayerStats->getLevelCap().at(mPlayerStats->getLevel() + 1)));
    mHealthValue.setString(std::format("{}/{}",
      mPlayerStats->getHealth(), mPlayerStats->getMaxHealth()));
    mAttackValue.setString(std::format("{}", mPlayerStats->getSecondaryStatValue(SecondaryStats::Attack)));
    mDamageValue.setString(std::format("{} - {}", mPlayerStats->getDamage().x,
      mPlayerStats->getDamage().y));
    mDefenceValue.setString(std::format("{}", mPlayerStats->getSecondaryStatValue(SecondaryStats::Defence)));
    mArmorValue.setString(std::format("{}", mPlayerStats->getArmor()));
    
    for (auto& [stat, text] : mPrimaryStatsValue) 
    {
      text.setString(std::format("{}", mPlayerStats->getPrimaryStatValue(stat)));
    }
    for (auto& [stat, text] : mSecondaryStatsValue)
    {
      text.setString(std::format("{}", mPlayerStats->getSecondaryStatValue(stat)));
    }
    
    mSkillPointsValue.setString(std::to_string(mPlayerStats->getSkillPoints()));
    for (auto& [skill, text] : mSkillsValue) {
      text.setString(std::format("{}", mPlayerStats->getSkillValue(skill)));
    }
    mNeedsUpdate = false;
  }
}

/**
 * @brief Draw the player's stats panel on the screen
 * @param window - window that draw
 */
 void PlayerStatsScreen::render(sf::RenderWindow& window) const
{
  if (mVisible) 
  {
    window.draw(mPanel);
    window.draw(mPlayerSprite);
    window.draw(mPlayerNameValue);
    window.draw(mLevelValue);
    window.draw(mLevelText);
    window.draw(mExpText);
    window.draw(mExpValue);
    window.draw(mHealthText);
    window.draw(mHealthValue);
    window.draw(mAttackText);
    window.draw(mAttackValue);
    window.draw(mDamageText);
    window.draw(mDamageValue);
    window.draw(mDefenceText);
    window.draw(mDefenceValue);
    window.draw(mArmorText);
    window.draw(mArmorValue);
    
    window.draw(mStatsDivider);
    window.draw(mStatsTitle);

    for (const auto& [stat, text] : mPrimaryStatsText) 
    {
      window.draw(text);
    }
    for (const auto& [stat, text] : mPrimaryStatsValue) 
    {
      window.draw(text);
    }
    for (const auto& [stat, text] : mSecondaryStatsText) 
    {
      window.draw(text);
    }
    for (const auto& [stat, text] : mSecondaryStatsValue) 
    {
      window.draw(text);
    }
    
    window.draw(mSkillsDivider);
    window.draw(mSkillsTitle);
    window.draw(mSkillPointsText);
    window.draw(mSkillPointsValue);
    for (const auto& [skill, text] : mSkillsText) 
    {
      window.draw(text);
    }
    for (auto& [stat, text] : mSkillsValue)
    {
      window.draw(text);
    }
  }
}

/**
 * @brief Show the panel
 */
void PlayerStatsScreen::show()
{
  mVisible = true;
  mNeedsUpdate = true;
}

/**
 * @brief Close the panel
 */
void PlayerStatsScreen::close()
{
  mVisible = false;
}

/**
 * @brief State of panel's visibility
 * @return if the panel is visible
 */
bool PlayerStatsScreen::isVisible() const
{
  return mVisible;
}