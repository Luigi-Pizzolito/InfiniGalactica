#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class StarField {
    private:
        sf::RenderWindow* m_window;
        const sf::Sprite* p_sprite;
        sf::Texture star_texture;
        sf::RenderStates star_rstate;
        int star_layc = 8;
        float parallax_c[8] = {0.875f, 0.75f, 0.625f, 0.5f, 0.375f, 0.25f, 0.125f, 0.0f};
        sf::VertexArray* star_layers[10];

        void genStars(sf::VertexArray* stars);
        void parallax();
        sf::Vector2f last_p;
    public:
        StarField(sf::RenderWindow* window, const sf::Sprite* sprite, int star_num);
        ~StarField();
        void draw();
};