#include "main_menu_screen.h"
#include "about_screen.h"
#include "adventure_screen.h"

/**
 * @brief For handling Events in handleInput method
 */

struct MainMenuScreen::ScreenInputVisitor
{
	MainMenuScreen& screen;
	sf::RenderWindow& window;

	void clearUI()
	{
		window.setMouseCursor(dr::CursorManager::get("arrow"));
		for (auto& button : screen.mMenuButtons)
		{
			button.clearOverlap();
		}
	}

	void operator()(const sf::Event::MouseMoved& mouseMoved)
	{
		sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseMoved.position);
		bool overlap = false;
		for (auto& button : screen.mMenuButtons)
		{
			if (button.isOverlap(mouseViewCoords))
			{
				overlap = true;
			}
		}

		// change the cursor
		if (overlap)
		{
			window.setMouseCursor(dr::CursorManager::get("hand"));
		}
		else
		{
			window.setMouseCursor(dr::CursorManager::get("arrow"));
		}
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
			if (screen.mMenuButtons[0].isClicked(mouseViewCoords))
			{
				clearUI();
				dr::ScreenManager::addScreen<AdventureScreen>("adventure_screen");
			}
			else if (screen.mMenuButtons[1].isClicked(mouseViewCoords))
			{
				clearUI();
				dr::ScreenManager::addScreen<AboutScreen>("about_screen");
			}
			else if (screen.mMenuButtons[2].isClicked(mouseViewCoords))
			{
				clearUI();
				dr::ScreenManager::destroyScreen();
			}
		}
	}

	void operator()(const auto&) {};
};

void MainMenuScreen::init()
{
	dr::TextButton playButton{ {250.f, 75.f}, dr::TextManager::get("main_menu_button") };
	playButton.setString(dr::StringManager::get("play_button"));
	playButton.setPosition({ 970.f, 780.f });
	mMenuButtons.push_back(playButton);

	dr::TextButton aboutButton{ {250.f, 75.f}, dr::TextManager::get("normal_button") };
	aboutButton.setString(dr::StringManager::get("about_button"));
	aboutButton.setPosition({ 970.f, 880.f });
	mMenuButtons.push_back(aboutButton);

	dr::TextButton exitButton{ {250.f, 75.f}, dr::TextManager::get("normal_button") };
	exitButton.setString(dr::StringManager::get("exit_button"));
	exitButton.setPosition({ 970.f, 980.f });
	mMenuButtons.push_back(exitButton);

	mTitle.setString(dr::StringManager::get("game_title"));
	mTitle.setPosition({900.f, 35.f});
}

void MainMenuScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	event.visit(ScreenInputVisitor{ *this, window });
}
void MainMenuScreen::update(float dt)
{ }
void MainMenuScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(mBackground);

	window.draw(mTitle);
	for (auto& button : mMenuButtons)
	{
		button.render(window);
	}
}