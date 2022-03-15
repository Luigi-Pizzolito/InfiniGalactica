#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class StarField {
    private:
        sf::RenderWindow* m_window;
        const sf::View* c_view;
        sf::Texture star_texture;
        sf::Texture nebula_texture;
        sf::RenderStates star_rstate;
        sf::RenderStates nebula_rstate;
        int star_layc = 8;
        int nebula_layc = 0;
        float parallax_c[8] = {0.96f, 0.89f, 0.82f, 0.75f, 0.68f, 0.61f, 0.54f, 0.47f}; // parallax plane distances, from 0.4f to close to 1.0f, calculated with y=0.4+\frac{0.6}{8.5}x
        std::vector<float> parallax_n_c;
        int star_num;
        float nebula_num;
        float nebula_begin_thres = 0.7f;      // threshold of distance when to beggin adding nebula layers
        sf::VertexArray* star_layers[8];
        std::vector<sf::VertexArray*> nebula_layers;

        void genStars(sf::VertexArray* stars);
        void genNebulas(sf::VertexArray* nebulas);
        void parallax();
        sf::Vector2f last_p;
    public:
        StarField(sf::RenderWindow* window, const sf::View* view, int star_num, float nebula_num);
        ~StarField();
        void draw();

        static void addElemtoVertexArray(sf::VertexArray* varray, const int oarray, const sf::Vector2f position, const sf::Vector2f size, const sf::Vector2i tex_size, const sf::Vector2i tex_ioffset);
};




class RadialStarField {
    private:
        sf::RenderWindow* m_window;
        const sf::View* c_view;
        sf::Texture star_texture;
        sf::RenderStates star_rstate;
        sf::VertexArray* stars;

        int star_num;
        const float speed;
        std::vector<sf::Vector3f> star_coords;

        void genStars();
        void travel();

    public:
        RadialStarField(sf::RenderWindow* window, const sf::View* view, int star_num, const float speed);
        ~RadialStarField();
        void draw();
};