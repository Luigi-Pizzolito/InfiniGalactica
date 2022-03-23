#include "Scenes/GameOver.h"
//todo: fix this scene not laoding properly
GameOver::GameOver(json cfg) {

	// Music
    // music = new MusicPlayer("song3", true);
    // music->update(0.9f);

    title.setString("Game Over");
    title_font.loadFromFile("res/Novel/LanaPixel.ttf");
    title.setFont(title_font);
    float c_siz = 150.0f;
    title.setCharacterSize(c_siz);
    // get the largest size that will fit in bounds with padding
    while (title.getGlobalBounds().width > Scene::s_view->getSize().x-Scene::s_view->getSize().x/8) {
        c_siz -=20;
        title.setCharacterSize(c_siz);
    }

    title.setOrigin(sf::Vector2f((-Scene::s_view->getSize().x/2)+(title.getGlobalBounds().width/2), -Scene::s_view->getSize().y/5));
    title.setFillColor(sf::Color::Red);

	sub.setString("Press Enter to Continue");
	sub.setFont(title_font);
	sub.setCharacterSize(44.0f);
	sub.setOrigin(sf::Vector2f((-Scene::s_view->getSize().x/2)+(title.getGlobalBounds().width/2), -Scene::s_view->getSize().y/2));
	sub.setFillColor(sf::Color::White);

	// Background
	rstarfield = new RadialStarField(Scene::s_window,Scene::s_view,(int)cfg["rstarfield"]["starNum"],(float)cfg["rstarfield"]["speed"]);

    f_in = new Composit::Fade(Scene::s_window, Scene::s_view, false, 2);
    f_in->trigger();
}

GameOver::~GameOver() {
	// delete music;
	delete rstarfield;
    delete f_in;
}

void GameOver::pollEvents() {
    	while (Scene::s_window->pollEvent(Scene::s_events))
	{
		// window events
		switch (Scene::s_events.type)
		{
		case sf::Event::Closed:
			s_window->close();
			break;
		case sf::Event::KeyPressed:
			if (s_events.key.code == sf::Keyboard::Enter) {
				m_return = true;
			}

			break;
		case sf::Event::KeyReleased:
            break;
		// No more type of events
		default:
			// This will change later
			break;
		}
	}
}

void GameOver::update(float delta_time) {
    pollEvents();
	if (m_return) {
		m_return = false;
		SceneManagement::goBackToMainMenu();
	}
}

void GameOver::render() {
	rstarfield->draw();
    Scene::s_window->draw(title);
	Scene::s_window->draw(sub);
    f_in->draw();
}