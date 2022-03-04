#include "StarField.h"
#include <random>

StarField::StarField(sf::RenderWindow* window, const sf::Sprite* sprite, int star_num):m_window(window),p_sprite(sprite) {
    for (int i = 0; i < star_layc; i++) {
        star_layers[i] = new sf::VertexArray(sf::Triangles, star_num*3);
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
    std::uniform_real_distribution<float> rs(0.5f,1.0f);    // generation bounds for star size

    // randomly distribute star positions
    float star_size;
    for (int i = 0; i < stars->getVertexCount();i++) {
        switch (i%3) {
            case 0:     //triangle vertex 1
                (*stars)[i].position = sf::Vector2f(rx(rng), ry(rng));
                star_size = rs(rng);
                break;
            case 1:     //triangle vertex 2
                (*stars)[i].position = (*stars)[i-1].position + sf::Vector2f(star_size, 1.8f*star_size);
                break;
            case 2:     //triangle vertex 3
                (*stars)[i].position = (*stars)[i-2].position + sf::Vector2f(-star_size, 1.8f*star_size);
                break;
            default:
                break;
        }
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