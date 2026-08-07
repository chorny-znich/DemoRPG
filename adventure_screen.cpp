#include "adventure_screen.h"

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
		screen.mCursor.handleInput(mouseMoved.position, window);
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
		}
	}

	void operator()(const auto&) {};
};

/**
 * @brief Initialize screen resources
 */
void AdventureScreen::init()
{
	mMapManager.loadMap(1);
	mCursor.setMapSize({ static_cast<int>(mMapManager.getCurrentMap().getMapSize().x),
		static_cast<int>(mMapManager.getCurrentMap().getMapSize().y) });
	mCursor.init();

	mPlayer.init();
}

void AdventureScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	event.visit(ScreenInputVisitor{ *this, window });
}

void AdventureScreen::update(float dt)
{
	mMainView.setCenter({ 960.f, 540.f });
	mCursor.update(dt);
	mPlayer.update(dt);
	//mMainView.setCenter({ 0.f, 0.f });
}

void AdventureScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(mMapManager.getCurrentMap());
	window.draw(mPlayer);
	mCursor.render(window);
	window.setView(mUIView);
}