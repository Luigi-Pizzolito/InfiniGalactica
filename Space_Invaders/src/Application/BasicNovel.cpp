#include "BasicNovel.h"
#include "SceneManager/TextPanel.h"

NovelGame::NovelGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name)
{
	// Load fonts
	font.loadFromFile("res/Novel/LanaPixel.ttf");
	// Load Textures
	dialog_overlay.loadFromFile("res/Novel/dialog_overlay.png");
	// Setting the textures
	// player.setTexture(player_texture);
	text_panel = new TextPanel(sf::String(L"你好，看起来玩玩儿在这个game! Hello, are you ready to play InfiniGalactica? If not you should hold on to your socks!  You really should play this otherwise imma whoops your lil' ass straight outta here you lil' who you think you are"),
		m_view->getSize().x - 50, font, 11 * 4, false);
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
}

void NovelGame::render()
{
	m_window->clear();

	// render background

	// renders objects
	// m_window->draw(player.getSprite());
	drawText();

	// displays objects on the screen
	m_window->display();
}

void NovelGame::drawText()
{
	// Draw dialog box
	sf::RectangleShape dialog_box = sf::RectangleShape(sf::Vector2f(0.0f, 0.0f));
	dialog_box.setSize(m_view->getSize());
	dialog_box.setTexture(&dialog_overlay);
	m_window->draw(dialog_box);

	// Create a text
	sf::Text text(text_panel->text(), font, 11 * 4);
	text.setOrigin(sf::Vector2f(-25.0f, -m_view->getSize().y + 20 + 44 * 2 + 10));
	text.setFillColor(sf::Color::White);
	text.setLineSpacing(0.8f);
	// Draw it
	m_window->draw(text);
}
