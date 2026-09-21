#include "player_actions.h"
#include "game_world.h"
#include "disreality_engine.h"
#include <iostream>

PlayerActions::PlayerActions(GameWorld& gameWorld)
{
	mActions = 
	{
		{ ActionType::PICK,
			{dr::StringManager::get("pick"), [&gameWorld](std::uint16_t id)
				{
					gameWorld.pickItem(id);
				}
			}
		}/*,
		{ ActionType::USE_LADDER,
			{"Use ladder", std::bind(&GameWorld::useLadder, this)}
		}*/
	};
}

void PlayerActions::add(ActionType type, std::uint16_t id)
{
	Action action = mActions.at(type);
	action.mLocID = id;
  mActionList.push_back(action);
}

const std::vector<Action>& PlayerActions::getCommands() const
{
	return mActionList;
}

bool PlayerActions::hasCommand() const
{
	return mActionList.size();
}