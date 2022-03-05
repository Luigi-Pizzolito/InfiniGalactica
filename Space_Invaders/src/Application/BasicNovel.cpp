#include "BasicNovel.h"
#include <iostream>
// #include <codecvt>

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


	// Load the panels
	panel_p = new std::vector<sf::String>(
		NovelGame::wrapTextPanelise(sf::String(L"你好，看起来玩玩儿在这个game! Hello, are you ready to play InfiniGalactica? If not you should hold on to your socks!  You really should play this otherwise imma whoops your lil' ass straight outta here you lil' fag"),
		m_view->getSize().x - 50, font, 11 * 4, false)
	);
	//  = &panels;
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
				next();
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
	sf::Text text(panel_p->at(panel_i), font, 11 * 4);
	text.setOrigin(sf::Vector2f(-25.0f, -m_view->getSize().y + 20 + 44 * 2 + 10));
	text.setFillColor(sf::Color::White);
	text.setLineSpacing(0.8f);
	// Draw it
	m_window->draw(text);
}

std::string NovelGame::ToUTF8(const sf::String &original)
	{
		std::string str;					// the final UTF-8 string
		str.resize(original.getSize() * 4); // worst case scenario:  4 bytes per codepoint

		std::string::iterator last = sf::Utf<32>::toUtf8(original.getData(), original.getData() + original.getSize(), str.begin());
		str.resize(last - str.begin());

		return str;
	}

bool NovelGame::next() {
	if (panel_i < panel_p->size()-1) {
		panel_i++;
		return true;
	} else {
		return false;
	}
}

std::vector<sf::String> NovelGame::wrapTextPanelise(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold)
{
	// Word wrap algorithim, finding the display length and adding \n or \31 alternatively, to add line breaks and separator \31 to indicate next panel
	unsigned currentOffset = 0;
	unsigned elip = font.getGlyph(' ', charicterSize, bold).advance + font.getGlyph(L'', charicterSize, bold).advance;
	bool firstWord = true;
	std::size_t wordBegining = 0;
	std::size_t line = 0;

	for (std::size_t pos(0); pos < string.getSize(); ++pos)
	{
		auto currentChar = string[pos];
		if (currentChar == '\n')
		{
			currentOffset = 0;
			firstWord = true;
			continue;
		}
		else if (currentChar == ' ')
		{
			wordBegining = pos;
			firstWord = false;
		}

		auto glyph = font.getGlyph(currentChar, charicterSize, bold);
		currentOffset += glyph.advance;

		if (!firstWord && currentOffset+elip > width)
		{
			pos = wordBegining;
			line++;
			string[pos] = line % 2 ? '\n' : '\31';
			firstWord = true;
			currentOffset = 0;
		}
	}


	// split string at separators \31 and push to array.
	std::vector<sf::String> panels;
	size_t sp = 0;
	size_t ep = 0;
	while (string.find(sf::String("\31")) != sf::String::InvalidPos) {
		ep = string.find(sf::String("\31"));
		panels.push_back(string.substring(sp, ep)+sf::String(L" ")); //add elipsis string if not on the last element
		string.erase(sp, (ep-sp)+1);
		sp = 0;
	}
	panels.push_back(string);
	

	// std::cout << ToUTF8(string) << "\n--START--\n";
	// for (size_t i = 0; i < panels.size(); i++)
	// {
	// 	std::cout << ToUTF8(  panels.at(i)  ) << "\n----\n";
	// }
	
	// m_window->close();
	return panels;
}