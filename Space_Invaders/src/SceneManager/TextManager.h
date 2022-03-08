#pragma once
#include "TextPanel.h"
#include <json.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class TextManager {
    private:
        // Constructor vars storage
        sf::RenderWindow* m_window;
        sf::View* m_view;
        bool* s_key;

        // Internal vars storage
        std::vector<TextPanel*> scenes_p;
        size_t scene_i = 0;

        // Layout/style parameters
        sf::Font font;
        const unsigned fontSize = 4*11; // Lana pixel works best in multiples of 11
    
        // Internal utility methods
        void loadScene();
    public:
        TextManager(sf::RenderWindow* m_window, sf::View* m_view, bool* s_key);
        ~TextManager();

        void next();
        void tick();
        void draw();
};