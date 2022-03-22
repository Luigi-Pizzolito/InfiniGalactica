#include "Composit.h"

namespace Composit {
    Fade::Fade(sf::RenderWindow* window, const sf::View* view, bool toBlack, int speed):window(window),view(view),type(toBlack),speed(speed) {
        alpha = (type) ? 0 : 255;
        rect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
        rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
        rect.setPosition(view->getCenter());
        rect.setScale(2.0f,2.0f);
        rect.setFillColor(sf::Color(0,0,0,0));
    }
    Fade::~Fade() {}
    void Fade::trigger() {
        state = true;
    }
    bool Fade::draw() {
        if (state) {
            rect.setFillColor(sf::Color(0,0,0,alpha));
            if ((type?255-alpha:alpha) > 0) {
                alpha += type ? speed : -speed;
            }
            alpha = (alpha > 255) ? 255 : ( (alpha < 0 ) ? 0 : alpha );  //clamp
            if (alpha == 255 || alpha == 0) {
                state = false;
                rect.setFillColor(sf::Color(0,0,0,(type) ? 255 : 0));
                return true;
            }
        }
        window->draw(rect);
        return false;
    }

    Portal::Portal(sf::RenderWindow* window, const sf::View* view, float lvl_length):window(window),view(view) {
        p_tex.loadFromFile("res/Sprites/effects/portal.png");
        portal.setSize(1.5f*sf::Vector2f(view->getSize().y,view->getSize().y));
        portal.setPosition((100.0f*lvl_length)+view->getSize().x-0.15f*portal.getSize().y, view->getSize().y/2.0f);
        portal.setOrigin(portal.getSize()/2.0f);
        portal.setTexture(&p_tex);
    }
    Portal::~Portal() {}
    void Portal::draw() {
        portal.rotate(2.0f);
        window->draw(portal);
    }
}