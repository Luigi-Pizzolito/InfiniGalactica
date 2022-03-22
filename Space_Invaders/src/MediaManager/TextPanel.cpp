#include "TextPanel.h"
#include <iostream>
#include "MediaManager/SFXPlayer.h"

TextPanel::TextPanel(sf::String string, const sf::String actor, const sf::Color highlight, const sf::Font &font, unsigned fontSize, sf::RenderWindow* m_window, sf::View* m_view, bool* s_key, std::string a_line, std::string actor_img_p, std::string background_p, bool bold):font(font), actor(actor), fontSize(fontSize),highlight(highlight),m_window(m_window),m_view(m_view),s_key(s_key),line(a_line),actor_img_p(actor_img_p),background_p(background_p) {
	// Word wrap algorithim, finding the display length and adding \n or \31 alternatively, to add line breaks and separator \31 to indicate next panel
	unsigned width = m_view->getSize().x - 2*(margin+border+padding);
	unsigned currentOffset = 0;
	unsigned elip = font.getGlyph(' ', fontSize, bold).advance + font.getGlyph(L'…', fontSize, bold).advance;
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

		auto glyph = font.getGlyph(currentChar, fontSize, bold);
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
	size_t sp = 0;
	size_t ep = 0;
	while (string.find(sf::String("\31")) != sf::String::InvalidPos) {
		ep = string.find(sf::String("\31"));
		panel_p.push_back(string.substring(sp, ep)+sf::String(L"…   ")); //add elipsis string if not on the last element
		string.erase(sp, (ep-sp)+1);
		sp = 0;
	}
	panel_p.push_back(string);

	// std::cout << ToUTF8(string) << "\n--START--\n";
	// for (size_t i = 0; i < panel_gen.size(); i++)
	// {
	// 	std::cout << ToUTF8(  panel_gen.at(i)  ) << "\n----\n";
	// }


	// Initialise static drawing parameters
	// dialog box
	float height = 2*((float)fontSize+padding);
	dialog_box.setPosition(sf::Vector2f(margin, m_view->getSize().y-height-margin));
	dialog_box.setSize(sf::Vector2f(m_view->getSize().x-2*margin, height));
	dialog_box.setFillColor(sf::Color::Black);
	dialog_box.setOutlineThickness(border);
	dialog_box.setOutlineColor(highlight);
	// next blinker
	textn.setCharacterSize(fontSize);
	textn.setFont(font);
	textn.setOrigin(sf::Vector2f(-margin-(m_view->getSize().x - 2*(margin+border+padding)),-m_view->getSize().y + (margin+border+padding) + fontSize - line_padding));
	textn.setFillColor(sf::Color(highlight.r,highlight.g,highlight.b,highlight.a/1.1));
	// main text
	text_d.setFont(font);
	text_d.setCharacterSize(fontSize);
	text_d.setFillColor(sf::Color::White);
	text_d.setLineSpacing(line_spacing);
	text_d.setOrigin(sf::Vector2f(-(margin+border+padding), -m_view->getSize().y + (margin+border+padding) + 2*fontSize + line_padding));
	// actor text
	actor_t.setFont(font);
	actor_t.setCharacterSize(fontSize);
	actor_t.setFillColor(sf::Color::White);
	actor_t.setString(actor);
	actor_t.setOrigin(sf::Vector2f(-(margin+border+padding), -m_view->getSize().y + (margin+border+padding) + 3*fontSize + line_padding + 3*border));
	// actor box
	actor_box.setPosition(sf::Vector2f(margin, m_view->getSize().y-(margin+border+padding+ 3*fontSize + line_padding + 3*border)));
	actor_box.setSize(sf::Vector2f(2*margin + actor_t.getLocalBounds().width, fontSize+2*border));
	actor_t.setString(actor+sf::String(":"));
	actor_box.setFillColor(sf::Color::Black);
	actor_box.setOutlineThickness(border);
	actor_box.setOutlineColor(highlight);
	//actor img
	loadTex();
	// actor_img.setTextureRect()
	sf::Vector2f a_size(m_view->getSize().x/4.5,m_view->getSize().y/2);
	// actor_img.setFillColor(sf::Color::White);
	actor_img.setSize(a_size);
	actor_img.setPosition(sf::Vector2f(margin-border, m_view->getSize().y-(margin+padding+ 3*fontSize + line_padding + 5*border)-a_size.y));
	// actor_img.setFillColor(sf::Color(255, 255, 255, 0));
	
	//background
	
	background.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
	background.setPosition(m_view->getCenter());
	background.setFillColor(sf::Color(255, 255, 255, 255));
	
}

void TextPanel::loadTex() {
	actor_img_tex.loadFromFile(actor_img_p);
	actor_img.setTexture(&actor_img_tex);
	background_texture.loadFromFile(background_p);
	background.setTexture(&background_texture);
}

TextPanel::~TextPanel() {
	panel_p.clear();
}

std::string TextPanel::ToUTF8(const sf::String &original)
	{
		std::string str;					// the final UTF-8 string
		str.resize(original.getSize() * 4); // worst case scenario:  4 bytes per codepoint

		std::string::iterator last = sf::Utf<32>::toUtf8(original.getData(), original.getData() + original.getSize(), str.begin());
		str.resize(last - str.begin());

		return str;
	}

bool TextPanel::next() {
	if (!(revealed < (this->text()).getSize()-1) && *s_key!=prev_key) { // only skip to next if showing the line is done, if the space key has just been pressed, if there are panels left if holding only FF, no skip
		if (panel_i < panel_p.size()-1) {	
			panel_i++;
			revealed = 0;
			reveal_b = 0;
			// *s_key = false;
			return false;
		} else {
			// no more panels to show, next text panel
			return true;
		}
	}
	return false;
}

sf::String TextPanel::text() {
	return panel_p.at(panel_i);
}

void TextPanel::tick() {
	tick_be++;
	if (panel_i < panel_p.size()-1) {
		tick_b++;
		blink_b = ((tick_b%((size_t)(60/(rate_b*2))+1))>(((60/(rate_b*2))+1)/4));
		if ((tick_b%((size_t)(60/(rate_b*2))+1)) == 0) {tick_b=0;}
	} else {
		blink_b = false;
	}

	if (reveal_b%(size_t)(60/reveal_s) == 0) {
		if (revealed < (this->text()).getSize()-1) {
			revealed += *s_key ? hold_s_boost : 1;
		}
	}
	reveal_b++;

	prev_key=*s_key;
}

void TextPanel::draw() {
	// Draw background
	if (background_p != "") {
		m_window->draw(background);
	}

	// Draw dialog box
	m_window->draw(dialog_box);

	// Create a main text
	sf::String draw_text(this->text());
	draw_text.replace(L"…  ", L"...");

	// letter by letter reveal
	if (revealed < draw_text.getSize()-1) {
		draw_text = draw_text.substring(0, revealed);
	}

	// if finished revealing
	if (!(revealed < (this->text()).getSize()-1)) {
		// ellipsis animation
		float rate_b_mod = (60/(rate_be*2))+1;
		const size_t tick_be_mod = tick_be%(size_t)rate_b_mod;
		if (tick_be_mod < (rate_b_mod/3)) {
			draw_text.replace(L"...", L".  ");
		} else if (tick_be_mod >= (rate_b_mod/3) && tick_be_mod < 2*(rate_b_mod/3)) {
			draw_text.replace(L"...", L".. ");
		} else if (tick_be_mod >= 2*(rate_b_mod/3) && tick_be_mod < rate_b_mod) {
			draw_text.replace(L"...", L"...");
		} if (tick_be_mod==rate_b_mod-1) {
			tick_be=0;
		}

		// next blinker
		textn.setString(blink_b ? L"\ue006" : L" ");
		m_window->draw(textn);
	}

	if (actor != "") {
		// Draw actor box and text
		m_window->draw(actor_box);
		m_window->draw(actor_t);
	}

	if (actor_img_p != "") {
		//draw actor img
		m_window->draw(actor_img);
	}

	if (line != "" && !line_p && !(*s_key)) {
		line_p = true;
		SFX::play(line, 80.0f);
	}

	// draw main text
	text_d.setString(draw_text);
	m_window->draw(text_d);

}