#include "Scenes/Credits.h"

Credits::Credits() {
    // Load Script
    fs_text = new FSScrollTextManager("res/credits.json", Scene::s_window, Scene::s_view, &key_space);

	// Music
    // music = new MusicPlayer("song3", true);
    // music->update(0.9f);

	// Background
	rstarfield = new RadialStarField(Scene::s_window,Scene::s_view,350,5.0f);
}

Credits::~Credits() {
    delete fs_text;
	// delete music;
	delete rstarfield;
}

void Credits::pollEvents() {
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
				std::cout << "SEGFAULT!\n";
				SceneManagement::goBackToMainMenu();			//!!! calling this here DOES causes segfault
			}

			if (Scene::s_events.key.code == sf::Keyboard::Space)
			{
				key_space = true;
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

void Credits::update(float delta_time) {
    pollEvents();
    if (fs_text->tick()) {
		SceneManagement::goBackToMainMenu();		//!!! calling this here DOES NOT causes segfault
	};
}

void Credits::render() {
	rstarfield->draw();
    fs_text->draw();
}