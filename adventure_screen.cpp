#include "adventure_screen.h"
#include "game_world.h"

#include <imgui.h>
#include <imgui-SFML.h>

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

	void operator()(const sf::Event::KeyPressed key)
	{
		if (key.code == sf::Keyboard::Key::P)
		{
			if (screen.mPlayerStatsScreen.isVisible())
			{
				screen.mPlayerStatsScreen.close();
			}
			else
			{
				screen.mPlayerStatsScreen.show();
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
	ImGui::SFML::Init(dr::ImguiHelper::getWindow());
	GameWorld::instance().init(mMainView);
	mPlayerStatsScreen.init(GameWorld::instance().getPlayer().getRPStatsComponent());
	dr::Log::instance().init({400.f, 250.f}, {5.f, 800.f}, "game_log");
	dr::Log::instance().addMessage("Start logging");
}

void AdventureScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	event.visit(ScreenInputVisitor{ *this, window });
	ImGui::SFML::ProcessEvent(window, event);
}

void AdventureScreen::update(float dt)
{
	ImGui::SFML::Update(dr::ImguiHelper::getWindow(), dr::ImguiHelper::getTime());
	GameWorld::instance().update(dt);
	mPlayerStatsScreen.update(dt);
	mMainView.setCenter(GameWorld::instance().getPlayer().getPosition());
	dr::Log::instance().update();
}

void AdventureScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(GameWorld::instance().getMapManager().getCurrentMap());

	for (const auto& obj : GameWorld::instance().getObjectManager().getObjects())
	{
		window.draw(obj->getSprite());
	}

	window.draw(GameWorld::instance().getPlayer());
	GameWorld::instance().getGridController().getCursorComponent().render(window);
	
	window.setView(mUIView);
	dr::Log::instance().render(window);
	mPlayerStatsScreen.render(window);

	ImGui::SFML::Render(window);
}