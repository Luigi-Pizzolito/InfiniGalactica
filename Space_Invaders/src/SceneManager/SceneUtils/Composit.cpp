#include "Composit.h"

namespace Composit {
    Fade::Fade(sf::RenderWindow* window, const sf::View* view, bool toBlack, int speed):window(window),view(view),type(toBlack),speed(speed) {
        alpha = (type) ? 0 : 255;
        rect.setOrigin(0,0);
        rect.setSize(view->getSize());
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
}