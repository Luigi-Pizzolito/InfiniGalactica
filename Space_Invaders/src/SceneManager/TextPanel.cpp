#include "TextPanel.h"
#include <iostream>

TextPanel::TextPanel(sf::String string, const sf::Font &font, unsigned fontSize,  sf::RenderWindow* m_window, sf::View* m_view, bool bold):font(font), fontSize(fontSize),m_window(m_window),m_view(m_view) {
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
	std::vector<sf::String> panel_gen;
	size_t sp = 0;
	size_t ep = 0;
	while (string.find(sf::String("\31")) != sf::String::InvalidPos) {
		ep = string.find(sf::String("\31"));
		panel_gen.push_back(string.substring(sp, ep)+sf::String(L" …")); //add elipsis string if not on the last element
		string.erase(sp, (ep-sp)+1);
		sp = 0;
	}
	panel_gen.push_back(string);

	// std::cout << ToUTF8(string) << "\n--START--\n";
	// for (size_t i = 0; i < panel_gen.size(); i++)
	// {
	// 	std::cout << ToUTF8(  panel_gen.at(i)  ) << "\n----\n";
	// }

	// Load the panels to pointer
	panel_p = new std::vector<sf::String>(panel_gen);
	panel_gen.clear();
}

TextPanel::~TextPanel() {
	panel_p->clear();
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
	if (panel_i < panel_p->size()-1) {
		panel_i++;
		return true;
	} else {
		return false;
	}
}

sf::String TextPanel::text() {
	return panel_p->at(panel_i);
}

void TextPanel::tick() {
	tick_b++;
}

void TextPanel::draw() {
	// Draw dialog box
	float height = 2*((float)fontSize+padding);
	sf::RectangleShape dialog_box = sf::RectangleShape();
	// std::cout << "h: " << height << "\n";
	dialog_box.setPosition(sf::Vector2f(margin, m_view->getSize().y-height-margin));
	dialog_box.setSize(sf::Vector2f(m_view->getSize().x-2*margin, height));
	// dialog_box.setTexture(&dialog_overlay);
	dialog_box.setFillColor(sf::Color::Black);
	dialog_box.setOutlineThickness(border);
	dialog_box.setOutlineColor(sf::Color::Cyan);
	m_window->draw(dialog_box);

	// Create a text
	sf::String draw_text(this->text());

	// ellipsis animation
	float rate_b_mod = (60/(rate_b*2))+1;
	const size_t tick_b_mod = tick_b%(size_t)rate_b_mod;
	if (tick_b_mod < (rate_b_mod/3)) {
		draw_text.replace(L" …", L".  ");
	} else if (tick_b_mod >= (rate_b_mod/3) && tick_b_mod < 2*(rate_b_mod/3)) {
		draw_text.replace(L" …", L".. ");
	} else if (tick_b_mod >= 2*(rate_b_mod/3) && tick_b_mod < rate_b_mod) {
		draw_text.replace(L" …", L"...");
	} if (tick_b_mod==rate_b_mod-1) {
		tick_b=0;
	}
	
	// draw_text.replace(L" …", blink_b ? L" " : L"…");
	sf::Text text(draw_text, font, fontSize);
	// sf::Vector2f origin = ;
	// std::cout << "x: " << origin.x << ", y: " << origin.y <<"\n";
	text.setOrigin(sf::Vector2f(-(margin+border+padding), -m_view->getSize().y + (margin+border+padding) + 2*fontSize + line_padding));
	text.setFillColor(sf::Color::White);
	text.setLineSpacing(line_spacing);
	// Draw it
	m_window->draw(text);
}