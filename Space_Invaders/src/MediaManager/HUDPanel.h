#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity/Player.h"

class HUDPanel {
    private:
        // Initialiser storage
        sf::RenderWindow* m_window;
        const sf::View* c_view;
        Player* player;
        const size_t* player_score;
        sf::Vector2f m_total_length;
        sf::Vector2f& m_progress;

        // Drawing vars
        sf::Font font;
        sf::Text score_t;
        sf::ConvexShape hud_bg;
        sf::RectangleShape hud_bars_bg1;
        sf::RectangleShape hud_bars_bg2;
        sf::RectangleShape h_bar;
        sf::RectangleShape l_bar;
        int hs_w;

        // Layout params
        const size_t fontSize = 11*5;
        const float padding = 10.0f;
        const int border = 2;

    public:
        HUDPanel(sf::RenderWindow* window, const sf::View* view, Player* player, const size_t* player_score,
            sf::Vector2f& position, const sf::Vector2f& total_length);
        ~HUDPanel();

        void draw();
};
