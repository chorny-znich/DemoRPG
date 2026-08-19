#pragma once
#include "rp_stats.h"
#include <string>
#include <map>
#include <unordered_map>
#include <SFML/System.hpp>
#include "game_data.h"

const size_t START_STATS_POINTS = 24;
const size_t MAX_HEALTH_MODIFIER = 3;
const float ATTACK_MODIFIER = 0.5;
const float RANGED_ATTACK_MODIFIER = 0.25;
const float DEFENCE_MODIFIER = 1.5;
const float ATTENTION_MODIFIER = 0.5;
const float REACTION_MODIFIER = 0.5;
const float REACTION_MODIFIER_DEXTERITY = 0.75;
const float REACTION_MODIFIER_PERCEPTION = 0.25;

/**
 * @brief The roleplay system
*/
class RPStatsComponent
{
protected:
	const std::map<uint16_t, uint16_t> LevelCap
	{
		{0, 0}, {1, 25}, {2, 100}, {3, 250}, {4, 500}, {5, 1000}
	};
	const std::map<size_t, std::unordered_map<std::string, size_t>> Adventurer
	{
		{1, {{"attack", 0}, {"defence", 0}, {"health", 5}, {"skill point", 1}}},
		{2, {{"attack", 0}, {"defence", 1}, {"health", 0}, {"skill point", 1}}},
		{3, {{"attack", 1}, {"defence", 0}, {"health", 5}, {"skill point", 1}}},
		{4, {{"attack", 0}, {"defence", 1}, {"health", 0}, {"skill point", 1}}},
		{5, {{"attack", 1}, {"defence", 0}, {"health", 5}, {"skill point", 2}}}
	};
	std::unordered_map<PrimaryStats, int> mPrimaryStats
	{
		{PrimaryStats::Strength, 1},
		{PrimaryStats::Stamina, 1},
		{PrimaryStats::Dexterity, 1},
		{PrimaryStats::Perception, 1},
		{PrimaryStats::Intellect, 1},
		{PrimaryStats::Charisma, 1}
	};
	std::unordered_map<SecondaryStats, int> mSecondaryStats
	{
		{SecondaryStats::Attack, 0},
		{SecondaryStats::Ranged_Attack, 0},
		{SecondaryStats::Defence, 0},
		{SecondaryStats::Attention, 0 },
		{SecondaryStats::Reaction, 0},
		{SecondaryStats::Sight, 0}
	};
	std::unordered_map<Skills, int> mSkills
	{
		{Skills::Search, 0},
		{Skills::Athletic, 0},
		{Skills::Dodge, 0 },
		{Skills::Deft_Hands, 0}
	};

private:
	std::string mName{ "Vargar" };
	size_t mLevel{ 0 };
	size_t mExperience{ 0 };
	size_t mExperienceForKill{ 25 };
	std::size_t mMoney{ 0 };
	size_t mBaseDefence{ 0 };
	sf::Vector2u mDamage{ 1, 2 };
	sf::Vector2u mRangedDamage{ 0, 0 };
	size_t mArmor{ 0 };
	size_t mMaxHealth{ 10 };
	size_t mBaseMaxHealth{ 10 };
	size_t mHealth{ 10 };
	//GameData::RPClass mClass{ GameData::RPClass::Adventurer };
	size_t mSkillPoints{ 0 };
	bool mLevelupMessage{ false };
public:
	void update();
	void setName(const std::string& name);
	const std::string& getName() const;

	// Level
	size_t getLevel() const;
	bool levelupCheck();
	void levelup();
	void showLevelupMessage(bool show);
	bool isLevelupMessageShow() const;

	void setExperience(size_t exp);
	void increaseExperience(size_t exp);
	size_t getExperience() const;
	size_t& getExperience();
	void setExperienceForKill(size_t exp);
	size_t getExperienceForKill() const;
	void setMoney(size_t money);
	void increaseMoney(size_t money);
	void decreaseMoney(size_t money);
	size_t getMoney() const;
	size_t& getMoney();
	void setBaseDefence(size_t value);
	//void updateDefence();
	void setDamage(sf::Vector2u dmg);
	sf::Vector2u getDamage() const;
	size_t getDamageValue() const;
	void setRangedDamage(sf::Vector2u rdmg);
	sf::Vector2u getRangedDamage() const;
	size_t getRangedDamageValue() const;
	void setArmor(size_t armor);
	size_t getArmor() const;
	void setMaxHealth(size_t value);
	size_t getMaxHealth() const;
	void setBaseMaxHealth(size_t value);
	void updateMaxHealth();
	void setHealth(size_t value);
	void increaseHealth(size_t value);
	void decreaseHealth(size_t value);
	size_t getHealth() const;
	void updateAttention();

	// Primary stats
	void increasePrimaryStat(PrimaryStats name);
	void decreasePrimaryStat(PrimaryStats name);
	size_t getPrimaryStatValue(PrimaryStats name);
	std::unordered_map<PrimaryStats, int>& getPrimaryStats();
	//void showPrimaryStats() const;
	// Secondary stats
	void setSecondaryStatValue(SecondaryStats stat, uint16_t value);
	size_t getSecondaryStatValue(SecondaryStats stat) const;
	std::unordered_map<SecondaryStats, int>& getSecondaryStats();
	//void showSecondaryStats() const;
	// Skills
	void setSkillValue(Skills name, uint16_t value);
	void increaseSkill(Skills name);
	uint16_t getSkillValue(Skills name);
	bool isSkillExist(Skills name) const;
	std::unordered_map<Skills, int>& getSkills();
	//std::string showSkills();
	//void increaseSkillPoints(size_t value);
	//void decreaseSkillPoints(size_t value);
	//size_t getSkillPoints() const;
	//void updateStatsFromSkills();

	const std::map<uint16_t, uint16_t>& getLevelCap() const;
	//std::unordered_map<std::string, size_t> getLevelupResult() const;
};