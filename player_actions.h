#pragma once
#include <string_view>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/System/String.hpp>

enum class ActionType
{
	PICK,
	USE_LADDER
};

struct Action
{
	sf::String mLabel{};
	std::function<void()> mFunc;
};

class GameWorld;

class PlayerActions
{
public:
	PlayerActions(GameWorld& gameWorld);
	void add(ActionType type);
	const std::vector<Action>& getCommands() const;
	bool hasCommand() const;
private:
	std::unordered_map<ActionType, Action> mActions;
	std::vector<Action> mActionList;
};