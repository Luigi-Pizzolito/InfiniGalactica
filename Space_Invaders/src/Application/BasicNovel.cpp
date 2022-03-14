#include "BasicNovel.h"
#include <iostream>
// #include "SceneManager/TextManager.h"

NovelGame::NovelGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name)
{
	// Load Script
	text_panel = new TextManager("res/Novel/Scenes/scene2.json", m_window, m_view, &key_space);

	music = new MusicPlayer("song1", true);
}

NovelGame::~NovelGame()
{
}

void NovelGame::pollEvents()
{
	while (m_window->pollEvent(m_events))
	{
		// window events
		switch (m_events.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			if (m_events.key.code == sf::Keyboard::Escape)
			{
				m_window->close();
			}

			if (m_events.key.code == sf::Keyboard::Space)
			{
				key_space = true;
				text_panel->next();
			}

			if (m_events.key.code == sf::Keyboard::Tab) {
				music->update(lvl_p);
				lvl_p+= 0.05f;
			}

			if (m_events.key.code == sf::Keyboard::LShift) {
				std::cout << "playing: " << music->position() << "\n";
			}

			break;
		case sf::Event::KeyReleased:
			if (m_events.key.code == sf::Keyboard::Space)
			{
				key_space = false;
			}
		// No more type of events
		default:
			// This will change later
			break;
		}
	}
	// react to space key here
}

void NovelGame::update()
{
	pollEvents();
	text_panel->tick();
}

void NovelGame::render()
{
	m_window->clear();

	// render background

	// renders objects
	// m_window->draw(player.getSprite());
	text_panel->draw();

	// displays objects on the screen
	m_window->display();
}

