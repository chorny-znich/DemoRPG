#pragma once
#include "game_data.h"
#include <disreality_engine.h>

class AdventureScreen : public dr::Screen
{
public:
	void init() override;
	void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
private:
	struct ScreenInputVisitor;

	sf::View mMainView{ {0, 0}, {gd::GraphicsResolution.x, gd::GraphicsResolution.y} };
	sf::View mUIView{ {0, 0}, {gd::GraphicsResolution.x, gd::GraphicsResolution.y} };

	dr::MapManager mMapManager;
};