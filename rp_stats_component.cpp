#include "rp_stats_component.h"

#include "rp_stats.h"
#include <disreality_engine.h>
#include <format>

void RPStatsComponent::update()
{
	/*ImGui::Begin("Player statistics");
	ImGui::Text(std::format("Name: {}", mName).c_str());
	ImGui::Text(std::format("Money: {}", mMoney).c_str());
	ImGui::End();*/
}

void RPStatsComponent::setName(const std::string& name)
{
	mName = name;
}
const std::string& RPStatsComponent::getName() const
{
	return mName;
}

size_t RPStatsComponent::getLevel() const
{
	return mLevel;
}

/**
 * @brief Check if the player gain a new level
 * @return
 */
bool RPStatsComponent::levelupCheck()
{
	if (mExperience >= LevelCap.at(mLevel + 1)) {
		levelup();
		return true;
	}

	return false;
}

void RPStatsComponent::levelup()
{
	mLevel++;
	/*setSecondaryStatValue(SecondaryStats::Attack, getSecondaryStatValue(SecondaryStats::Attack) +
		Adventurer.at(mLevel).at(SecondaryStats::Attack));
	setSecondaryStatValue(SecondaryStats::Defence, getSecondaryStatValue(SecondaryStats::Defence) + 
		Adventurer.at(mLevel).at(SecondaryStats::Defence));
	updateMaxHealth();*/
	//increaseSkillPoints(Adventurer.at(mLevel).at("skill point"));
}

void RPStatsComponent::showLevelupMessage(bool show)
{
	mLevelupMessage = show;
}

bool RPStatsComponent::isLevelupMessageShow() const
{
	return mLevelupMessage;
}

void RPStatsComponent::setExperience(size_t exp)
{
	mExperience = exp;
}

void RPStatsComponent::increaseExperience(size_t exp)
{
	mExperience += exp;
}

size_t RPStatsComponent::getExperience() const
{
	return mExperience;
}

size_t& RPStatsComponent::getExperience()
{
	return mExperience;
}

void RPStatsComponent::setExperienceForKill(size_t exp)
{
	mExperienceForKill = exp;
}

size_t RPStatsComponent::getExperienceForKill() const
{
	return mExperienceForKill;
}

void RPStatsComponent::setMoney(size_t money)
{
	mMoney = money;
}

void RPStatsComponent::increaseMoney(size_t money)
{
	mMoney += money;
}

void RPStatsComponent::decreaseMoney(size_t money)
{
	mMoney = (money > mMoney) ? 0 : mMoney - money;
}

size_t RPStatsComponent::getMoney() const
{
	return mMoney;
}

size_t& RPStatsComponent::getMoney()
{
	return mMoney;
}

void RPStatsComponent::setBaseDefence(size_t value)
{
	mBaseDefence = value;
}
/*
void RPStatsComponent::updateDefence()
{
	size_t result = mBaseDefence;
	/*for (size_t i = 1; i < mLevel; i++) {
		result += Adventurer.at(i).at("defence");
	}*/ /*
	result += mSkills.at("Dodge");
	setSecondaryStatValue("Defence", result);
}
*/
void RPStatsComponent::setDamage(sf::Vector2u dmg)
{
	mDamage = dmg;
}

sf::Vector2u RPStatsComponent::getDamage() const
{
	return mDamage;
}

size_t RPStatsComponent::getDamageValue() const
{
	return dr::EngineUtility::getRandomInRange(mDamage.x, mDamage.y);
}

void RPStatsComponent::setRangedDamage(sf::Vector2u rdmg)
{
	mRangedDamage = rdmg;
}

sf::Vector2u RPStatsComponent::getRangedDamage() const
{
	return mRangedDamage;
}

size_t RPStatsComponent::getRangedDamageValue() const
{
	return dr::EngineUtility::getRandomInRange(mRangedDamage.x, mRangedDamage.y);
}

void RPStatsComponent::setArmor(size_t armor)
{
	mArmor = armor;
}

size_t RPStatsComponent::getArmor() const
{
	return mArmor;
}

/**
 * @brief Set the value of player's maximum possible health
 * @param value Maximum player's health
 */
void RPStatsComponent::setMaxHealth(size_t value)
{
	mMaxHealth = value;
}

size_t RPStatsComponent::getMaxHealth() const
{
	return mMaxHealth;
}

void RPStatsComponent::setBaseMaxHealth(size_t value)
{
	mBaseMaxHealth = value;
}

void RPStatsComponent::updateMaxHealth()
{
	size_t result = mBaseMaxHealth;
	for (size_t i = 1; i <= mLevel; i++) {
		result += Adventurer.at(i).at("health");
	}
	//result += mSkills.at("Athletic") * 5;
	setMaxHealth(result);
}

void RPStatsComponent::setHealth(size_t value)
{
	mHealth = value;
}

void RPStatsComponent::increaseHealth(size_t value)
{
	if (mMaxHealth >= mHealth + value) {
		mHealth += value;
	}
	else {
		mHealth = mMaxHealth;
	}
}

void RPStatsComponent::decreaseHealth(size_t value)
{
	mHealth = (mHealth > value) ? mHealth - value : 0;
}

size_t RPStatsComponent::getHealth() const
{
	return mHealth;
}

/**
 * @brief Update secondary stat - Attention which depends on
 *	primary stat Perception and skill Search
*/
void RPStatsComponent::updateAttention()
{
	setSecondaryStatValue(SecondaryStats::Attention, std::floor(getPrimaryStatValue(PrimaryStats::Perception)
		* ATTENTION_MODIFIER) + getSkillValue(Skills::Search));
}

void RPStatsComponent::setSecondaryStatValue(SecondaryStats name, uint16_t value)
{
	mSecondaryStats.at(name) = value;
}

size_t RPStatsComponent::getSecondaryStatValue(SecondaryStats name) const
{
	return mSecondaryStats.at(name);
}
std::unordered_map<SecondaryStats, int>& RPStatsComponent::getSecondaryStats()
{
	return mSecondaryStats;
}
/*
void RPStatsComponent::showSecondaryStats() const
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

void RPStatsComponent::showPrimaryStats() const
{
	std::cout << "Primary stats:\n";
	for (const auto& stat : mPrimaryStats) {
		std::cout << std::format("  {} - {}\n", stat.first, stat.second);
	}
	std::cout << "\n";
}
*/ 
void RPStatsComponent::increasePrimaryStat(PrimaryStats name)
{
	mPrimaryStats.at(name) += 1;
}

void RPStatsComponent::decreasePrimaryStat(PrimaryStats name)
{
	mPrimaryStats.at(name) -= 1;
}

size_t RPStatsComponent::getPrimaryStatValue(PrimaryStats name)
{
	return mPrimaryStats.at(name);
}
std::unordered_map<PrimaryStats, int>& RPStatsComponent::getPrimaryStats()
{
	return mPrimaryStats;
}

void RPStatsComponent::setSkillValue(Skills name, uint16_t value)
{
	mSkills.at(name) = value;
}

void RPStatsComponent::increaseSkill(Skills name)
{
	mSkills.at(name) += 1;
}

uint16_t RPStatsComponent::getSkillValue(Skills name)
{
	return mSkills.at(name);
}
std::unordered_map<Skills, int>& RPStatsComponent::getSkills()
{
	return mSkills;
}

bool RPStatsComponent::isSkillExist(Skills name) const
{
	return (mSkills.find(name) != mSkills.end()) ? true : false;
}
/*
std::string RPStatsComponent::showSkills()
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
void RPStatsComponent::increaseSkillPoints(size_t value)
{
	mSkillPoints += value;
}

void RPStatsComponent::decreaseSkillPoints(size_t value)
{
	mSkillPoints -= value;
}

size_t RPStatsComponent::getSkillPoints() const
{
	return mSkillPoints;
}
*/
/**
 * @brief 
 * @return 
 */
const std::map<uint16_t, uint16_t>& RPStatsComponent::getLevelCap() const
{
	return LevelCap;
}
/*
// Get result of the last player's level up
std::unordered_map<std::string, size_t> RPStatsComponent::getLevelupResult() const
{
	return Adventurer.at(mLevel);
}

/*
size_t RPStatsComponent::getSkillPoints() const
{
	return mSkillPoints;
}

void RPStatsComponent::updateStatsFromSkills()
{
	updateMaxHealth();
	updateDefence();
	updateAttention();
}*/