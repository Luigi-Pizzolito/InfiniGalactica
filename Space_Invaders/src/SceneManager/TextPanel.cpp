#include "TextPanel.h"
#include <iostream>

TextPanel::TextPanel(sf::String string, const sf::Font &font, unsigned fontSize, const sf::Color highlight, sf::RenderWindow* m_window, sf::View* m_view, bool* s_key, bool bold):font(font), fontSize(fontSize),highlight(highlight),m_window(m_window),m_view(m_view),s_key(s_key) {
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
	// Draw dialog box
	float height = 2*((float)fontSize+padding);
	sf::RectangleShape dialog_box = sf::RectangleShape();
	dialog_box.setPosition(sf::Vector2f(margin, m_view->getSize().y-height-margin));
	dialog_box.setSize(sf::Vector2f(m_view->getSize().x-2*margin, height));
	// dialog_box.setTexture(&dialog_overlay);
	dialog_box.setFillColor(sf::Color::Black);
	dialog_box.setOutlineThickness(border);
	dialog_box.setOutlineColor(highlight);
	m_window->draw(dialog_box);

	// Create a text
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
		sf::Text textn(blink_b ? L"" : L" ", font, fontSize);
		textn.setOrigin(sf::Vector2f(-margin-(m_view->getSize().x - 2*(margin+border+padding)),-m_view->getSize().y + (margin+border+padding) + fontSize - line_padding));
		textn.setFillColor(sf::Color(highlight.r,highlight.g,highlight.b,highlight.a/1.1));
		m_window->draw(textn);
	}
	
	// create main text
	sf::Text text(draw_text, font, fontSize);
	text.setOrigin(sf::Vector2f(-(margin+border+padding), -m_view->getSize().y + (margin+border+padding) + 2*fontSize + line_padding));
	text.setFillColor(sf::Color::White);
	text.setLineSpacing(line_spacing);

	// Draw it
	m_window->draw(text);
}