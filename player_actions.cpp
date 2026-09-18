#include "player_actions.h"
#include "game_world.h"
#include "disreality_engine.h"

PlayerActions::PlayerActions(GameWorld& gameWorld)
{
	mActions = 
	{
		{ ActionType::PICK,
			{dr::StringManager::get("pick"), [&gameWorld]()
				{
					gameWorld.pickItem();
				}
			}
		}/*,
		{ ActionType::USE_LADDER,
			{"Use ladder", std::bind(&GameWorld::useLadder, this)}
		}*/
	};
}

void PlayerActions::add(ActionType type)
{
  mActionList.push_back(mActions.at(type));
}

const std::vector<Action>& PlayerActions::getCommands() const
{
	return mActionList;
}

bool PlayerActions::hasCommand() const
{
	return mActionList.size();
}