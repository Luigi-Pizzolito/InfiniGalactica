#include "Scenes/BasicNovel.h"
#include <iostream>

NovelGame::NovelGame()
{
	// Load Script
	text_panel = new TextManager("res/Novel/Scenes/scene2.json", Scene::s_window, Scene::s_view, &key_space);

	music = new MusicPlayer("song4", true);
}

NovelGame::~NovelGame()
{
}

void NovelGame::pollEvents()
{
	while (Scene::s_window->pollEvent(Scene::s_events))
	{
		// window events
		switch (Scene::s_events.type)
		{
		case sf::Event::Closed:
			Scene::s_window->close();
			break;
		case sf::Event::KeyPressed:
			if (Scene::s_events.key.code == sf::Keyboard::Escape)
			{
				Scene::s_window->close();
			}

			if (Scene::s_events.key.code == sf::Keyboard::Space)
			{
				key_space = true;
				text_panel->next();
			}

			if (Scene::s_events.key.code == sf::Keyboard::Tab) {
				music->update(lvl_p);
				lvl_p+= 0.05f;
			}

			if (Scene::s_events.key.code == sf::Keyboard::LShift) {
				std::cout << "playing: " << music->position() << "\n";
			}

			if (Scene::s_events.key.code == sf::Keyboard::Backspace) {
				m_return = true;
			}

			break;
		case sf::Event::KeyReleased:
			if (Scene::s_events.key.code == sf::Keyboard::Space)
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



void NovelGame::update(float delta_time)
{
	pollEvents();
	text_panel->tick();
}

void NovelGame::render()
{
	//m_window->clear();

	// render background

	// renders objects
	// m_window->draw(player.getSprite());
	text_panel->draw();

	//// displays objects on the screen
	//m_window->display();
}

