#include "rp_stats_component.h"

#include "rp_stats.h"
#include <disreality_engine.h>
#include <format>

void RPStats::update()
{
	/*ImGui::Begin("Player statistics");
	ImGui::Text(std::format("Name: {}", mName).c_str());
	ImGui::Text(std::format("Money: {}", mMoney).c_str());
	ImGui::End();*/
}

void RPStats::setName(const std::string& name)
{
	mName = name;
}
const std::string& RPStats::getName() const
{
	return mName;
}

size_t RPStats::getLevel() const
{
	return mLevel;
}

/**
 * @brief Check if the player gain a new level
 * @return
 */
bool RPStats::levelupCheck()
{
	if (mExperience >= LevelCap.at(mLevel + 1)) {
		levelup();
		return true;
	}

	return false;
}

void RPStats::levelup()
{
	mLevel++;
	/*setSecondaryStatValue(SecondaryStats::Attack, getSecondaryStatValue(SecondaryStats::Attack) +
		Adventurer.at(mLevel).at(SecondaryStats::Attack));
	setSecondaryStatValue(SecondaryStats::Defence, getSecondaryStatValue(SecondaryStats::Defence) + 
		Adventurer.at(mLevel).at(SecondaryStats::Defence));
	updateMaxHealth();*/
	//increaseSkillPoints(Adventurer.at(mLevel).at("skill point"));
}

void RPStats::showLevelupMessage(bool show)
{
	mLevelupMessage = show;
}

bool RPStats::isLevelupMessageShow() const
{
	return mLevelupMessage;
}

void RPStats::setExperience(size_t exp)
{
	mExperience = exp;
}

void RPStats::increaseExperience(size_t exp)
{
	mExperience += exp;
}

size_t RPStats::getExperience() const
{
	return mExperience;
}

size_t& RPStats::getExperience()
{
	return mExperience;
}

void RPStats::setExperienceForKill(size_t exp)
{
	mExperienceForKill = exp;
}

size_t RPStats::getExperienceForKill() const
{
	return mExperienceForKill;
}

void RPStats::setMoney(size_t money)
{
	mMoney = money;
}

void RPStats::increaseMoney(size_t money)
{
	mMoney += money;
}

void RPStats::decreaseMoney(size_t money)
{
	mMoney = (money > mMoney) ? 0 : mMoney - money;
}

size_t RPStats::getMoney() const
{
	return mMoney;
}

size_t& RPStats::getMoney()
{
	return mMoney;
}

void RPStats::setBaseDefence(size_t value)
{
	mBaseDefence = value;
}
/*
void RPStats::updateDefence()
{
	size_t result = mBaseDefence;
	/*for (size_t i = 1; i < mLevel; i++) {
		result += Adventurer.at(i).at("defence");
	}*/ /*
	result += mSkills.at("Dodge");
	setSecondaryStatValue("Defence", result);
}
*/
void RPStats::setDamage(sf::Vector2u dmg)
{
	mDamage = dmg;
}

sf::Vector2u RPStats::getDamage() const
{
	return mDamage;
}

size_t RPStats::getDamageValue() const
{
	return dr::EngineUtility::getRandomInRange(mDamage.x, mDamage.y);
}

void RPStats::setRangedDamage(sf::Vector2u rdmg)
{
	mRangedDamage = rdmg;
}

sf::Vector2u RPStats::getRangedDamage() const
{
	return mRangedDamage;
}

size_t RPStats::getRangedDamageValue() const
{
	return dr::EngineUtility::getRandomInRange(mRangedDamage.x, mRangedDamage.y);
}

void RPStats::setArmor(size_t armor)
{
	mArmor = armor;
}

size_t RPStats::getArmor() const
{
	return mArmor;
}

/**
 * @brief Set the value of player's maximum possible health
 * @param value Maximum player's health
 */
void RPStats::setMaxHealth(size_t value)
{
	mMaxHealth = value;
}

size_t RPStats::getMaxHealth() const
{
	return mMaxHealth;
}

void RPStats::setBaseMaxHealth(size_t value)
{
	mBaseMaxHealth = value;
}

void RPStats::updateMaxHealth()
{
	size_t result = mBaseMaxHealth;
	for (size_t i = 1; i <= mLevel; i++) {
		result += Adventurer.at(i).at("health");
	}
	//result += mSkills.at("Athletic") * 5;
	setMaxHealth(result);
}

void RPStats::setHealth(size_t value)
{
	mHealth = value;
}

void RPStats::increaseHealth(size_t value)
{
	if (mMaxHealth >= mHealth + value) {
		mHealth += value;
	}
	else {
		mHealth = mMaxHealth;
	}
}

void RPStats::decreaseHealth(size_t value)
{
	mHealth = (mHealth > value) ? mHealth - value : 0;
}

size_t RPStats::getHealth() const
{
	return mHealth;
}

/**
 * @brief Update secondary stat - Attention which depends on
 *	primary stat Perception and skill Search
*/
void RPStats::updateAttention()
{
	setSecondaryStatValue(SecondaryStats::Attention, std::floor(getPrimaryStatValue(PrimaryStats::Perception)
		* ATTENTION_MODIFIER) + getSkillValue(Skills::Search));
}

void RPStats::setSecondaryStatValue(SecondaryStats name, uint16_t value)
{
	mSecondaryStats.at(name) = value;
}

size_t RPStats::getSecondaryStatValue(SecondaryStats name) const
{
	return mSecondaryStats.at(name);
}
std::unordered_map<SecondaryStats, int>& RPStats::getSecondaryStats()
{
	return mSecondaryStats;
}
/*
void RPStats::showSecondaryStats() const
{
	std::cout << "Secondary stats:\n";
	std::cout << std::format("  Money - {}\n", getMoney());
	std::cout << std::format("  Health - {}\n", getMaxHealth());
	std::cout << std::format("  Attack - {}\n", getSecondaryStatValue("Attack"));
	std::cout << std::format("  Ranged attack - {}\n", getSecondaryStatValue("Ranged attack"));
	std::cout << std::format("  Defence - {}\n", getSecondaryStatValue("Defence"));
	std::cout << std::format("  Attention - {}\n", getSecondaryStatValue("Attention"));
	std::cout << std::format("  Reaction - {}\n", getSecondaryStatValue("Reaction"));
	std::cout << "\n";
}

void RPStats::showPrimaryStats() const
{
	std::cout << "Primary stats:\n";
	for (const auto& stat : mPrimaryStats) {
		std::cout << std::format("  {} - {}\n", stat.first, stat.second);
	}
	std::cout << "\n";
}
*/ 
void RPStats::increasePrimaryStat(PrimaryStats name)
{
	mPrimaryStats.at(name) += 1;
}

void RPStats::decreasePrimaryStat(PrimaryStats name)
{
	mPrimaryStats.at(name) -= 1;
}

size_t RPStats::getPrimaryStatValue(PrimaryStats name)
{
	return mPrimaryStats.at(name);
}
std::unordered_map<PrimaryStats, int>& RPStats::getPrimaryStats()
{
	return mPrimaryStats;
}

void RPStats::setSkillValue(Skills name, uint16_t value)
{
	mSkills.at(name) = value;
}

void RPStats::increaseSkill(Skills name)
{
	mSkills.at(name) += 1;
}

uint16_t RPStats::getSkillValue(Skills name)
{
	return mSkills.at(name);
}
std::unordered_map<Skills, int>& RPStats::getSkills()
{
	return mSkills;
}

bool RPStats::isSkillExist(Skills name) const
{
	return (mSkills.find(name) != mSkills.end()) ? true : false;
}
/*
std::string RPStats::showSkills()
{
	std::string result{};
	result.append("Skills:\n");
	for (const auto& [skill, value] : mSkills) {
		result.append(std::format("  {} -- {}\n", skill, value));
	}
	result.append("\n");

	return result;
}
*/ /*
void RPStats::increaseSkillPoints(size_t value)
{
	mSkillPoints += value;
}

void RPStats::decreaseSkillPoints(size_t value)
{
	mSkillPoints -= value;
}

size_t RPStats::getSkillPoints() const
{
	return mSkillPoints;
}
std::map<size_t, size_t> RPStats::getLevelCap() const
{
	return LevelCap;
}

// Get result of the last player's level up
std::unordered_map<std::string, size_t> RPStats::getLevelupResult() const
{
	return Adventurer.at(mLevel);
}

/*
size_t RPStats::getSkillPoints() const
{
	return mSkillPoints;
}

void RPStats::updateStatsFromSkills()
{
	updateMaxHealth();
	updateDefence();
	updateAttention();
}*/