#include "Scenes/NovelScene.h"
#include <iostream>

// todo: update music progress based on text panel progress

NovelLevel::NovelLevel(json cfg)
{
	// Load Script
	text_panel = new TextManager(std::string("res/Novel/Scenes/")+std::string(cfg["novelScene"])+std::string(".json"), Scene::s_window, Scene::s_view, &key_space);

	music = new MusicPlayer(std::string(cfg["music"]), true);
}

NovelLevel::~NovelLevel()
{
	delete text_panel;
	delete music;
}

void NovelLevel::pollEvents()
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
				m_return = true;
			}

			if (Scene::s_events.key.code == sf::Keyboard::Space)
			{
				key_space = true;
				if (text_panel->next()) {
					m_return = true;
				};
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

}



void NovelLevel::update(float delta_time)
{
	pollEvents();
	text_panel->tick();

	music->update(text_panel->scene_p());

	if (m_return) {
		m_return = false;
		SceneManagement::goBackToMainMenu();
	}
}

void NovelLevel::render()
{
	text_panel->draw();
}

