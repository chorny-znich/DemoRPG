#pragma once
#include "game_data.h"
#include <unordered_map>
#include <vector>
#include <disreality_engine.h>

/**
 * @brief For Entities to know its environment 
 */

using Environment = std::unordered_map<gd::MapDirections, std::vector<dr::Location*>>;

class EnvironmentComponent
{
public:
  void spawn(dr::Map* map);
  void check(gd::Position pos, int sight);
private:
  dr::Map* mCurrentMap{ nullptr };
  Environment mEnvironment;
};