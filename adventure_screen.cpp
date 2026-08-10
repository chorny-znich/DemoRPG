#include "adventure_screen.h"
#include "game_world.h"

/**
 * @brief For handling Events in handleInput method
 */
struct AdventureScreen::ScreenInputVisitor
{
	AdventureScreen& screen;
	sf::RenderWindow& window;

	void clearUI()
	{
		window.setMouseCursor(dr::CursorManager::get("arrow"));
	}

	void operator()(const sf::Event::MouseMoved& mouseMoved)
	{
		sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseMoved.position);
		GameWorld::instance().getGridController().handleInput(mouseMoved.position, window);
		GameWorld::instance().checkMovementPossibility();
		
	}

	/**
	 * @brief Mouse button clicked event
	 * @param
	 */
	void operator()(const sf::Event::MouseButtonPressed mouseButton)
	{
		if (mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseButton.position);
			if (GameWorld::instance().checkMovementPossibility() && 
				GameWorld::instance().getGameplayState() == GameplayState::PLAYER_INPUT)
			{
				GameWorld::instance().startMovePlayer();
			}
		}
	}

	void operator()(const auto&) {};
};

/**
 * @brief Initialize screen resources
 */
void AdventureScreen::init()
{
	GameWorld::instance().init(mMainView);
}

void AdventureScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	event.visit(ScreenInputVisitor{ *this, window });
}

void AdventureScreen::update(float dt)
{
	mMainView.setCenter({ 960.f, 540.f });
	GameWorld::instance().update(dt);
	//mMainView.setCenter({ 0.f, 0.f });
}

void AdventureScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(GameWorld::instance().getMapManager().getCurrentMap());
	window.draw(GameWorld::instance().getPlayer());
	GameWorld::instance().getGridController().getCursorComponent().render(window);
	window.setView(mUIView);
}