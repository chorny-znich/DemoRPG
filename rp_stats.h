#pragma once
#include <cstdint>
#include <unordered_map>
#include <string_view>

enum class PrimaryStats : std::uint8_t
{
  Strength,
  Stamina, 
  Dexterity,
  Perception,
  Intellect,
  Charisma,
  COUNT
};

enum class SecondaryStats : std::uint8_t
{
  Attack,
  Ranged_Attack,
  Defence,
  Attention,
  Reaction,
  Sight
};

enum class Skills : std::uint8_t
{
  Search,
  Athletic,
  Dodge,
  Deft_Hands
};

inline std::unordered_map<PrimaryStats, std::string_view> mPrimaryStatsName
{
  {PrimaryStats::Strength, "Strength"},
  {PrimaryStats::Stamina, "Stamina"},
  {PrimaryStats::Dexterity, "Dexterity"},
  {PrimaryStats::Perception, "Perception"},
  {PrimaryStats::Intellect, "Intellect"},
  {PrimaryStats::Charisma, "Charisma"}
};

inline std::unordered_map<SecondaryStats, std::string_view> mSecondaryStatsName
{
  {SecondaryStats::Attack, "Attack"},
  {SecondaryStats::Ranged_Attack, "Ranged attack"},
  {SecondaryStats::Defence, "Defence"},
  {SecondaryStats::Attention, "Attention"},
  {SecondaryStats::Reaction, "Reaction"},
  {SecondaryStats::Sight, "Sight"}
};

inline std::unordered_map<Skills, std::string_view> mSkillsName
{
  {Skills::Search, "Search"},
  {Skills::Athletic, "Athletic"},
  {Skills::Dodge, "Dodge"},
  {Skills::Deft_Hands, "Deft hands"}
};