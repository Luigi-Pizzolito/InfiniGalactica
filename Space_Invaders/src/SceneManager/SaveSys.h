#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "SceneManager/SceneUtils/SelectionMenu.h"

class PauseSc {
    private:
        sf::RenderWindow* window;
        const sf::View* view;
        SelectionMenu* selec;

        bool returnToMenu = false;
        bool* paused;
        std::string scene_name;

        sf::RectangleShape bg;

    public:
        PauseSc(sf::RenderWindow* window, const sf::View* view, bool* paused, std::string scene_name); //todo add score here
        ~PauseSc();

        bool draw();
        void pre();
        void update();
        void handleInput(sf::Event event);
};