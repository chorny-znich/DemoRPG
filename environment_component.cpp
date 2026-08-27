#include "environment_component.h"

/**
 * @brief 
 * @param map Raw pointer to the current map. Must be calling when changing a map
 */
void EnvironmentComponent::spawn(dr::Map* map)
{
	mCurrentMap = map;
}

/**
 * @brief Check a situation in the entites field of view
 * @param pos Position on the map in tile coordinates
 * @param sight Entity characteristic. Field of the view 
 */
void EnvironmentComponent::check(gd::Position pos, int sight)
{
	mEnvironment.clear();

	for (uint16_t i{ 1 }; i < static_cast<uint16_t>(gd::MapDirections::COUNT); i++)
	{
		for (uint16_t j{ 1 }; j <= sight; j++)
		{
			dr::Location* loc = &mCurrentMap->getLocation(pos.first + gd::mCoordDirections[i].first * j +
				(pos.second + gd::mCoordDirections[i].second * j) * mCurrentMap->getMapSize().x);
			mEnvironment[static_cast<gd::MapDirections>(i)].push_back(loc);
			if (!loc->mPassable)
			{
				break;
			}
		}
	}
}

const Environment& EnvironmentComponent::get() const
{
	return mEnvironment;
}