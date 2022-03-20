#pragma once
#include "TextPanel.h"
#include <json.hpp>
using json = nlohmann::json;
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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

        float scene_p() {
            // get the scene progress percentage in order to update the music in the level
            return ((float)scene_i+1.0f)/(float)scenes_p.size();
        }
};

class FSScrollTextManager {
    private:
        // Constructor vars storage
        sf::RenderWindow* m_window;
        sf::View* m_view;
        bool* s_key;

        // Internal vars storage
        sf::Text fs_text;
        sf::Vector2f t_pos;

        // Layout/style parameters
        sf::Font font;
        const unsigned fontSize = 4*11;
        const float line_spacing = 1.0f;
        const float horz_margin = m_view->getSize().x/8;
        const float vert_margin = m_view->getSize().y/6;
        const float hold_s_boost = 4.0f;

        // Internal utility methods
        void loadScene(json obj);
        sf::String addLineWrap(sf::String string);

    public:
        FSScrollTextManager(json obj, sf::RenderWindow* m_window, sf::View* m_view, bool* s_key);
        ~FSScrollTextManager();

        bool tick();
        void draw();
};