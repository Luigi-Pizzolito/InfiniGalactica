#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class StarField {
    private:
        sf::RenderWindow* m_window;
        const sf::View* c_view;
        sf::Texture star_texture;
        sf::RenderStates star_rstate;
        int star_layc = 8;
        float parallax_c[8] = {0.96f, 0.89f, 0.82f, 0.75f, 0.68f, 0.61f, 0.54f, 0.47f}; // parallax plane distances, from 0.4f to close to 1.0f, calculated with y=0.4+\frac{0.6}{8.5}x
        int star_num;
        sf::VertexArray* star_layers[8];

        void addElemtoVertexArray(sf::VertexArray* varray, const int oarray, const sf::Vector2f position, const sf::Vector2f size, const sf::Vector2i tex_size, const sf::Vector2i tex_ioffset);
        void genStars(sf::VertexArray* stars);
        void parallax();
        sf::Vector2f last_p;
    public:
        StarField(sf::RenderWindow* window, const sf::View* view, int star_num);
        ~StarField();
        void draw();
};