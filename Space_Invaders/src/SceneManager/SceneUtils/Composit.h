#pragma once
#include <SFML/Graphics.hpp>

namespace Composit {
    class Fade {
        private:
            sf::RenderWindow* window;
            const sf::View* view;
            sf::RectangleShape rect;

            bool state = false;
            int speed = 2;
            bool type;
            int alpha;
        public:
            Fade(sf::RenderWindow* window, const sf::View* view, bool toBlack, int speed);
            ~Fade();

            void trigger();
            bool draw();
    };

    class Portal {
        private:
            sf::RenderWindow* window;
            const sf::View* view;
            sf::Texture p_tex;
            sf::RectangleShape portal;
        public:
            Portal(sf::RenderWindow* window, const sf::View* view, float lvl_length);
            ~Portal();
            void draw();
    };
}