#pragma once
#include "rp_stats_component.h"
#include <disreality_engine.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

/**
 * @brief Screen with player's statistic
 */
class PlayerStatsScreen
{
public:
  PlayerStatsScreen();
  void init(RPStatsComponent* stats);
  void update(float dt);
  void render(sf::RenderWindow& window) const;

  void show();
  void close();
  bool isVisible() const;
private:
  RPStatsComponent* mPlayerStats{nullptr};

  const sf::Vector2f PANEL_SIZE{400.f, 575.f};
  const sf::Color PANEL_COLOR{ 0, 0, 0, 225 };
  sf::RectangleShape mPanel{ PANEL_SIZE };
  
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
  std::unordered_map<PrimaryStats, sf::Text> mPrimaryStatsText;
  std::unordered_map<PrimaryStats, sf::Text> mPrimaryStatsValue;
  std::unordered_map<SecondaryStats, sf::Text> mSecondaryStatsText;
  std::unordered_map<SecondaryStats, sf::Text> mSecondaryStatsValue;
  
  sf::RectangleShape mSkillsDivider;
  sf::Text mSkillsTitle;
  sf::Text mSkillPointsText;
  sf::Text mSkillPointsValue;
  std::unordered_map<Skills, sf::Text> mSkillsText;
  std::unordered_map<Skills, sf::Text> mSkillsValue;

  std::unordered_map<Skills, dr::ImageButton> mSkillsPlusButtons;
  std::unordered_map<Skills, dr::ImageButton> mSkillsMinusButtons;
  std::unordered_map<Skills, sf::Text> mSkillsCalcValues;

  bool mNeedsUpdate{ false };
};