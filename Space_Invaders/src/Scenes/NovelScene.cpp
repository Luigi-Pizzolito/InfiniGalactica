#include "Scenes/NovelScene.h"
#include <iostream>




NovelLevel::NovelLevel(json cfg)
{
	// Load Script
	text_panel = new TextManager(std::string("res/Novel/Scenes/")+std::string(cfg["novelScene"])+std::string(".json"), Scene::s_window, Scene::s_view, &key_space);

	music = new MusicPlayer(std::string(cfg["music"]), true);

	f_in = new Composit::Fade(s_window, s_view, false, 4);
	f_out = new Composit::Fade(s_window, s_view, true, 4);
	f_in->trigger();
}

NovelLevel::~NovelLevel()
{
	delete text_panel;
	delete music;
	delete f_in;
	delete f_out;
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
					// m_return = true;
					f_out->trigger();
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
	f_in->draw();
	if (f_out->draw()) {
		m_return = true;
	}
}

