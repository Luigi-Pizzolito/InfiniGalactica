#pragma once
#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class TextPanel {
    private:
        sf::RenderWindow* m_window;
        sf::View* m_view;
        sf::Color highlight;
        const sf::Font font;
        const unsigned fontSize;
        const float margin = 20;
        const float border = 5;
        const float padding = 10;
        const float line_spacing = 0.8f;
        const float line_padding = 5;
        const float rate_be = 0.5;
        const float rate_b = 2;

        size_t tick_b = 0; 
        size_t tick_be = 0; 
        bool blink_b = false;

        size_t panel_i = 0;
        std::vector<sf::String>* panel_p;
        static std::string ToUTF8(const sf::String &original);
    public:
        TextPanel(sf::String string, const sf::Font &font, unsigned fontSize, sf::Color highlight, sf::RenderWindow* m_window, sf::View* m_view, bool bold = false);
        ~TextPanel();
        sf::String text();
        bool next();

        void tick();
        void draw();
};