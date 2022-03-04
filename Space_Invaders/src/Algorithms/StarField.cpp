#include "StarField.h"
#include <random>

StarField::StarField(sf::RenderWindow* window, const sf::Sprite* sprite, int star_num):m_window(window),p_sprite(sprite) {
    for (int i = 0; i < star_layc; i++) {
        star_layers[i] = new sf::VertexArray(sf::Points, star_num);
        addStars(star_layers[i]);
    }
}

StarField::~StarField() {}

void StarField::addStars(sf::VertexArray* stars) {
    // randomly generate and set the star positions

    std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> rx(-0.25f*m_window->getSize().x,m_window->getSize().x*4); // generation bounds for star field
	std::uniform_int_distribution<int> ry(-0.25f*m_window->getSize().y,m_window->getSize().y*4); // 

    // randomly distribute player positions
    for (int i = 0; i < stars->getVertexCount();i++) {
        (*stars)[i].position = sf::Vector2f(rx(rng), ry(rng));
    }
}

void StarField::parallax() {
    // shift stars compensating for player position

    sf::Vector2f delta_p = p_sprite->getPosition() - last_p; // get the vector of player movement since last frame
    delta_p.y = 0.0f;       // do not compensate for y

    // for each layer
    for (int l = 0; l < star_layc; l++) {
        for (int i = 0; i < star_layers[l]->getVertexCount();i++) {
            (*star_layers[l])[i].position += delta_p * parallax_c[l];                  // compensate star position based on player movement
        }                                                                              // multiply compensation coeeficient to create different depths
    }

    // update last position
    last_p = p_sprite->getPosition();
}

void StarField::draw() {
    // Apply parallax
    parallax();
    // Draw vertex arrays of stars
    for (int i = 0; i < star_layc; i++) {
        m_window->draw(*(star_layers[i]));
    }
}