#pragma once
#include "game_world.h"
#include "player.h"
#include "player_stats_screen.h"
#include "game_data.h"
#include <disreality_engine.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

class AdventureScreen : public dr::Screen
{
public:
	void init() override;
	void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
private:
	struct ScreenInputVisitor;

	sf::View mMainView{ {gd::GraphicsResolution.x / 2.f, gd::GraphicsResolution.y / 2.f}, 
		{gd::GraphicsResolution.x, gd::GraphicsResolution.y} };
	sf::View mUIView{ {gd::GraphicsResolution.x / 2.f, gd::GraphicsResolution.y / 2.f}, 
		{gd::GraphicsResolution.x, gd::GraphicsResolution.y} };

	PlayerStatsScreen mPlayerStatsScreen;
};