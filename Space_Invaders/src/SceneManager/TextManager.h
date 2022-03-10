#pragma once
#include "TextPanel.h"
#include <json.hpp>
using json = nlohmann::json;
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//Class Implemented by Luigi 08.03 10:43
class TextManager {
    private:
        // Constructor vars storage
        const std::string file;
        sf::RenderWindow* m_window;
        sf::View* m_view;
        bool* s_key;

        // Internal vars storage
        std::vector<TextPanel> scenes_p;
        size_t scene_i = 0;

        // Layout/style parameters
        sf::Font font;
        const unsigned fontSize = 4*11; // Lana pixel works best in multiples of 11
    
        // Internal utility methods
        void loadScene();
    public:
        TextManager(std::string scene, sf::RenderWindow* m_window, sf::View* m_view, bool* s_key);
        ~TextManager();

        bool next();
        void tick();
        void draw();
};