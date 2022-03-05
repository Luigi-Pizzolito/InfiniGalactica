#pragma once
#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class TextPanel {
    private:
        size_t panel_i = 0;
        std::vector<sf::String>* panel_p;
        static std::string ToUTF8(const sf::String &original);
    public:
        TextPanel(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold = false);
        ~TextPanel();
        sf::String text();
        bool next();
};