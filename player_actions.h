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
	std::function<void(std::uint16_t)> mFunc;
	std::uint16_t mLocID{0};
};

class GameWorld;

class PlayerActions
{
public:
	PlayerActions(GameWorld& gameWorld);
	void add(ActionType type, std::uint16_t id);
	const std::vector<Action>& getCommands() const;
	bool hasCommand() const;
	void clear();
private:
	std::unordered_map<ActionType, Action> mActions;
	std::vector<Action> mActionList;
};