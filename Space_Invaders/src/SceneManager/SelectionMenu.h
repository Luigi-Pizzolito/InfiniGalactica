#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

class SelectionMenu {
    private:
        sf::RenderWindow* m_window;
        const sf::View* c_view;

        sf::Font font;
        sf::Text selection_t;
        sf::Text pointer_t;
        const int font_s = 44;
        const int selec_off = font_s+12;

        int selection_i = 0;
        std::vector<std::string> options;

        void updateLayout();

    public:
        SelectionMenu(sf::RenderWindow* window, const sf::View* view);
        ~SelectionMenu();
        void draw();
        void addOptions(std::string single_option);
        void addOptions(std::vector<std::string> multiple_option);
        void clearOptions() { options.clear(); }
        std::string selection() { return options[selection_i]; }
        void handleInput(sf::Event event);
        bool selected = false;
};