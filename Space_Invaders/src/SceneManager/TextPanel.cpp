#include "TextPanel.h"
// #include <iostream>

TextPanel::TextPanel(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold) {
	// Word wrap algorithim, finding the display length and adding \n or \31 alternatively, to add line breaks and separator \31 to indicate next panel
	unsigned currentOffset = 0;
	unsigned elip = font.getGlyph(' ', charicterSize, bold).advance + font.getGlyph(L'…', charicterSize, bold).advance;
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