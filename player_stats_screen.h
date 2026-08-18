#pragma once
#pragma once
#include "rp_stats_component.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

/**
 * @brief Screen with player's statistic
 */
class PlayerStatsScreen
{
public:
  PlayerStatsScreen(RPStatsComponent& stats);
  void update(sf::Time dt);
  void render(sf::RenderWindow& window);

  void show();
  void close();
  bool isVisible() const;
private:
  RPStatsComponent& mPlayerStats;
  const sf::Vector2f PANEL_SIZE{ 400.f, 575.f };
  const sf::Vector2f POSITION{ 500.f, 400.f };
  sf::RectangleShape mPanel{ PANEL_SIZE };
  const sf::Color mPanelColor{ 0, 0, 0, 225 };
  bool mVisible{ false };

  sf::Sprite mPlayerSprite;
  sf::Text mPlayerNameValue;
  sf::Text mLevelText;
  sf::Text mLevelValue;
  sf::Text mExpText;
  sf::Text mExpValue;
  sf::Text mHealthText;
  sf::Text mHealthValue;
  sf::Text mAttackText;
  sf::Text mAttackValue;
  sf::Text mDefenceText;
  sf::Text mDefenceValue;
  sf::Text mDamageText;
  sf::Text mDamageValue;
  sf::Text mArmorText;
  sf::Text mArmorValue;

  sf::RectangleShape mStatsDivider;
  sf::Text mStatsTitle;
  std::unordered_map<std::string, sf::Text> mPrimaryStatsText;
  std::unordered_map<std::string, sf::Text> mPrimaryStatsValue;
  std::unordered_map<std::string, sf::Text> mSecondaryStatsText;
  std::unordered_map<std::string, sf::Text> mSecondaryStatsValue;

  sf::RectangleShape mSkillsDivider;
  sf::Text mSkillsTitle;
  sf::Text mSkillPointsText;
  sf::Text mSkillPointsValue;
  std::unordered_map<std::string, sf::Text> mSkillsText;
  std::unordered_map<std::string, sf::Text> mSkillsValue;

  std::unordered_map<std::string, dr::ImageButton> mSkillsPlusButtons;
  std::unordered_map<std::string, dr::ImageButton> mSkillsMinusButtons;
  std::unordered_map<std::string, sf::Text> mSkillsCalcValues;
};