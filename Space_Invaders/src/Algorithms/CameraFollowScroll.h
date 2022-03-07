#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity/Player.h"

class CameraFollowHorzScroll {
    private:
        sf::RenderWindow* window;
        sf::View* view;
        Player* player;
        sf::Vector2f c_speed;
        sf::Vector2f last_p;
        sf::Vector2f p_last_p;
        // float max_player_speed;
        float mapF(float value, float istart, float istop, float ostart, float ostop);
    public:
        CameraFollowHorzScroll(sf::RenderWindow* window, sf::View* view, Player* player, sf::Vector2f c_speed);
        ~CameraFollowHorzScroll();
        void follow();
};