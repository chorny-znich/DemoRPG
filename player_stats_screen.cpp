#include "player_stats_screen.h"
#include "game_data.h"
#include <disreality_engine.h>
#include <format>

/**
 * @brief 
 * @param stats 
 */
PlayerStatsScreen::PlayerStatsScreen(RPStatsComponent& stats) :
  mPlayerStats{ stats },
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

  mPrimaryStatsText{
    {"Strength", dr::TextManager::get("player_stats_screen_title")},
    {"Stamina", dr::TextManager::get("player_stats_screen_title")},
    {"Dexterity", dr::TextManager::get("player_stats_screen_title")},
    {"Perception", dr::TextManager::get("player_stats_screen_title")},
    {"Intellect", dr::TextManager::get("player_stats_screen_title")},
    {"Charisma", dr::TextManager::get("player_stats_screen_title")}
  },
  mPrimaryStatsValue{
    {"Strength", dr::TextManager::get("player_stats_screen_value")},
    {"Stamina", dr::TextManager::get("player_stats_screen_value")},
    {"Dexterity", dr::TextManager::get("player_stats_screen_value")},
    {"Perception", dr::TextManager::get("player_stats_screen_value")},
    {"Intellect", dr::TextManager::get("player_stats_screen_value")},
    {"Charisma", dr::TextManager::get("player_stats_screen_value")}
  },
  mSecondaryStatsText{
   {"Attention", dr::TextManager::get("player_stats_screen_title")},
   {"Reaction", dr::TextManager::get("player_stats_screen_title")},
   {"Sight", dr::TextManager::get("player_stats_screen_title")},
  },
  mSecondaryStatsValue{
  {"Attention", dr::TextManager::get("player_stats_screen_value")},
  {"Reaction", dr::TextManager::get("player_stats_screen_value")},
  {"Sight", dr::TextManager::get("player_stats_screen_value")},
  },
  mSkillsDivider{ {PANEL_SIZE.x - 100.f, 5.f} },
  mSkillsTitle{ dr::TextManager::get("player_stats_screen_title") },
  mSkillPointsText{ dr::TextManager::get("player_stats_screen_title") },
  mSkillPointsValue{ dr::TextManager::get("player_stats_screen_value") },
  mSkillsText{
  {"Search", dr::TextManager::get("player_stats_screen_title")},
  {"Athletic", dr::TextManager::get("player_stats_screen_title")},
  {"Dodge", dr::TextManager::get("player_stats_screen_title")},
  {"Deft hands", dr::TextManager::get("player_stats_screen_title")}
  },
  mSkillsValue{
  {"Search", dr::TextManager::get("player_stats_screen_value")},
  {"Athletic", dr::TextManager::get("player_stats_screen_value")},
  {"Dodge", dr::TextManager::get("player_stats_screen_value")},
  {"Deft hands", dr::TextManager::get("player_stats_screen_value")},
  },
  mSkillsPlusButtons{
  {"Search", dr::ImageButton({64.f, 64.f}, "plus_button")},
  {"Athletic", dr::ImageButton({64.f, 64.f}, "plus_button")},
  {"Dodge", dr::ImageButton({64.f, 64.f}, "plus_button")},
  {"Deft hands", dr::ImageButton({64.f, 64.f}, "plus_button")}
  }
{
  mPanel.setPosition({
    GameData::GraphicResolution.x / 2 - PANEL_SIZE.x / 2,
    GameData::GraphicResolution.y / 2 - PANEL_SIZE.y / 2
    });
  mPanel.setFillColor(mPanelColor);

  const sf::Vector2f PANEL_POSITION = mPanel.getPosition();

  mPlayerSprite.setTexture(dr::Textures::get("player"));
  mPlayerSprite.setTextureRect({ static_cast<int>(dr::Database::getSprite("player_idle_1").x),
    static_cast<int>(dr::Database::getSprite("player_idle_1").y),
    24, 32 });
  mPlayerSprite.setScale({ 3.f, 3.f });
  mPlayerSprite.setPosition({ PANEL_POSITION.x + 10.f, PANEL_POSITION.y + 20.f });

  // Setup text
  mPlayerNameValue.setPosition({ PANEL_POSITION.x + 125.f, PANEL_POSITION.y + 20.f });
  mPlayerNameValue.setString(mPlayerStats.getName());
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

  mStatsDivider.setPosition(PANEL_POSITION.x + 45.f, PANEL_POSITION.y + 165.f);
  mStatsDivider.setFillColor(sf::Color(255, 239, 213, 200));

  mStatsTitle.setPosition(PANEL_POSITION.x + PANEL_SIZE.x / 2 - 100.f, PANEL_POSITION.y + 172.f);
  mStatsTitle.setString("Primary/Secondary stats");

  sf::Vector2f startPosition{ PANEL_POSITION.x + 25.f, PANEL_POSITION.y + 205.f };
  const float VERT_STEP{ 25.f };
  int iteration{ 0 };

  for (auto& [stat, text] : mPrimaryStatsText) {
    text.setPosition(startPosition.x, startPosition.y + iteration * VERT_STEP);
    text.setString(stat);
    iteration++;
  }

  iteration = 0;
  for (auto& [stat, text] : mPrimaryStatsValue) {
    text.setPosition(startPosition.x + 125.f, startPosition.y + iteration * VERT_STEP);
    text.setString("");
    iteration++;
  }

  iteration = 0;
  for (auto& [stat, text] : mSecondaryStatsText) {
    text.setPosition(startPosition.x + 200.f, startPosition.y + iteration * VERT_STEP);
    text.setString(stat);
    iteration++;
  }

  iteration = 0;
  for (auto& [stat, text] : mSecondaryStatsValue) {
    text.setPosition(startPosition.x + 325.f, startPosition.y + iteration * VERT_STEP);
    text.setString("");
    iteration++;
  }

  mSkillsDivider.setPosition(startPosition.x + 25.f, startPosition.y + 175.f);
  mSkillsDivider.setFillColor(sf::Color(255, 239, 213, 200));

  mSkillsTitle.setPosition(startPosition.x + PANEL_SIZE.x / 2 - 50.f, startPosition.y + 182.f);
  mSkillsTitle.setString("Skills");

  mSkillPointsText.setPosition(startPosition.x, startPosition.y + 210.f);
  mSkillPointsText.setString("Skill points");
  mSkillPointsValue.setPosition(startPosition.x + 125.f, startPosition.y + 210.f);
  mSkillPointsValue.setString("");


  iteration = 0;
  for (auto& [skill, text] : mSkillsText) {
    text.setPosition(startPosition.x, startPosition.y + 245.f + iteration * VERT_STEP);
    text.setString(skill);
    iteration++;
  }

  iteration = 0;
  for (auto& [skill, text] : mSkillsValue) {
    text.setPosition(startPosition.x + 125.f, startPosition.y + 245.f + iteration * VERT_STEP);
    text.setString("");
    iteration++;
  }
}

/**
 * @brief update the logic
 * @param dt - time that the single frame takes
 */
void PlayerStats::update(sf::Time dt)
{
  if (mVisible) {
    mLevelValue.setString(std::to_string(mPlayerStats.getLevel()));
    mExpValue.setString(std::format("{}/{}", mPlayerStats.getExperience(),
      mPlayerStats.getLevelCap().at(mPlayerStats.getLevel() + 1)));
    mHealthValue.setString(std::format("{}/{}",
      mPlayerStats.getHealth(), mPlayerStats.getMaxHealth()));
    mAttackValue.setString(std::format("{}", mPlayerStats.getSecondaryStatValue("Attack")));
    mDamageValue.setString(std::format("{} - {}", mPlayerStats.getDamage().x,
      mPlayerStats.getDamage().y));
    mDefenceValue.setString(std::to_string(mPlayerStats.getSecondaryStatValue("Defence")));
    mArmorValue.setString(std::to_string(mPlayerStats.getArmor()));

    for (auto& [stat, text] : mPrimaryStatsValue) {
      text.setString(std::to_string(mPlayerStats.getPrimaryStatValue(stat)));
    }
    for (auto& [stat, text] : mSecondaryStatsValue) {
      text.setString(std::to_string(mPlayerStats.getSecondaryStatValue(stat)));
    }

    mSkillPointsValue.setString(std::to_string(mPlayerStats.getSkillPoints()));
    for (auto& [skill, text] : mSkillsValue) {
      text.setString(std::to_string(mPlayerStats.getSkillValue(skill)));
    }
  }
}

/**
 * @brief Draw the player's stats panel on the screen
 * @param window - window that draw
 */
void PlayerStats::render(sf::RenderWindow& window)
{
  if (mVisible) {
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

    for (auto& [stat, text] : mPrimaryStatsText) {
      window.draw(text);
    }
    for (auto& [stat, text] : mPrimaryStatsValue) {
      window.draw(text);
    }
    for (auto& [stat, text] : mSecondaryStatsText) {
      window.draw(text);
    }
    for (auto& [stat, text] : mSecondaryStatsValue) {
      window.draw(text);
    }

    window.draw(mSkillsDivider);
    window.draw(mSkillsTitle);
    window.draw(mSkillPointsText);
    window.draw(mSkillPointsValue);
    for (auto& [skill, text] : mSkillsText) {
      window.draw(text);
    }
    for (auto& [stat, text] : mSkillsValue) {
      window.draw(text);
    }
  }
}

/**
 * @brief Show the panel
 */
void PlayerStats::show()
{
  mVisible = true;
}

/**
 * @brief Close the panel
 */
void PlayerStats::close()
{
  mVisible = false;
}

/**
 * @brief State of panel's visibility
 * @return if the panel is visible
 */
bool PlayerStats::isVisible() const
{
  return mVisible;
}