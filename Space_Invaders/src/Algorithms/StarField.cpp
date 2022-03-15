#include "StarField.h"
#include <random>
#include <iostream>

// todo: add asteroids and nebulas in the background as well.

StarField::StarField(sf::RenderWindow* window, const sf::View* view, int star_num, float nebula_num):m_window(window),c_view(view),star_num(star_num),nebula_num(nebula_num) {
    // set star texture
    star_texture.loadFromFile("res/Sprites/stars.png");
    star_rstate.texture = &star_texture;
    // set nebula texture
    nebula_texture.loadFromFile("res/Sprites/nebulas.png");
    nebula_rstate.texture = &nebula_texture;

    // populate vertex arrays with vertices
    // for stars
    for (int i = 0; i < star_layc; i++) {
        int quad_num = star_num*4 * std::pow(1+parallax_c[i], 5);
        quad_num -= quad_num%4; // ensure quad num is a multiple of 4
        std::cout << "generated " << quad_num/4.0f << " stars at depth " << parallax_c[i] << "\n";
        if ( parallax_c[i] > nebula_begin_thres ) {
            // if the layer is far back enough, also generate some nebulas, so add nebula layer and parallax coef. + offset
            nebula_layc++;
            parallax_n_c.push_back(parallax_c[i]+0.025f);
        }

        star_layers[i] = new sf::VertexArray(  sf::Quads,  quad_num  );  // slowly moving layers need more stars as they are further streched out
        genStars(star_layers[i]);
    }
    // for nebulas
    for (int i = 0; i < nebula_layc; i++) {
        int quad_num = nebula_num*4 * std::pow(1+parallax_n_c[i], 3);
        quad_num -= quad_num%4; // ensure quad num is a multiple of 4
        std::cout << "generated " << quad_num/4.0f << " nebulas at depth " << parallax_n_c[i] << "\n";
        nebula_layers.push_back(  new sf::VertexArray( sf::Quads, quad_num )  );
        genNebulas(nebula_layers[i]);
    }
}

StarField::~StarField() {}

void StarField::addElemtoVertexArray(sf::VertexArray* varray, const int oarray, const sf::Vector2f position, const sf::Vector2f size, const sf::Vector2i tex_size, const sf::Vector2i tex_ioffset) {
    // generate position and texture coordinates for each vertex

    // set position coordinates of each vertex
    (*varray)[oarray*4   ].position  =  position                                                    ;
    (*varray)[oarray*4 +1].position  =  (*varray)[oarray*4].position  +  sf::Vector2f(size.x, 0.0f) ;
    (*varray)[oarray*4 +2].position  =  (*varray)[oarray*4].position  +  size                       ;
    (*varray)[oarray*4 +3].position  =  (*varray)[oarray*4].position  +  sf::Vector2f(0.0f, size.y) ;
    // set texture coordinates of each vertex
    sf::Vector2f spritesheet_offset   =  sf::Vector2f(tex_size.x*tex_ioffset.x, tex_size.y*tex_ioffset.y );
    (*varray)[oarray*4   ].texCoords  =  spritesheet_offset                                               ;
    (*varray)[oarray*4 +1].texCoords  =  spritesheet_offset  +  sf::Vector2f(  tex_size.x,  0.0f        ) ;
    (*varray)[oarray*4 +2].texCoords  =  spritesheet_offset  +  sf::Vector2f(  tex_size.x,  tex_size.y  ) ;
    (*varray)[oarray*4 +3].texCoords  =  spritesheet_offset  +  sf::Vector2f(  0.0f      ,  tex_size.y  ) ;
}

void StarField::genStars(sf::VertexArray* stars) {
    // randomly generate and set the star positions

    // setup random generation
    std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int>      rx(-0.25f*c_view->getSize().x,c_view->getSize().x*4); // generation bounds for star field
	std::uniform_int_distribution<int>      ry(0.0f,c_view->getSize().y); // 
    std::uniform_real_distribution<float>   rs(2.0f,8.0f);    // generation bounds for star size
    std::uniform_int_distribution<int>      rt(0, 4);            // random texture

    // randomly distribute star positions
    for (int i = 0; i < stars->getVertexCount()/4;i++) {
        float r_size = rs(rng);
        addElemtoVertexArray(stars, i, sf::Vector2f(rx(rng), ry(rng)), sf::Vector2f(r_size, r_size), sf::Vector2i(8, 8), sf::Vector2i(rt(rng), 0));
    }
}

void StarField::genNebulas(sf::VertexArray* nebulas) {
    // randomly generate and set the nebula positions

    // setup random generation
    std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int>      rx(-0.25f*c_view->getSize().x,c_view->getSize().x*4); // generation bounds for nebula field
	std::uniform_int_distribution<int>      ry(-100.0f,c_view->getSize().y-450.0f); // 
    std::uniform_real_distribution<float>   rs(200.0f,1000.0f);    // generation bounds for nebula size
    std::uniform_int_distribution<int>      rt(0, 6);            // random texture

    // randomly distribute nebula positions
    for (int i = 0; i < nebulas->getVertexCount()/4;i++) {
        float r_size = rs(rng);
        addElemtoVertexArray(nebulas, i, sf::Vector2f(rx(rng), ry(rng)), sf::Vector2f(r_size, r_size), sf::Vector2i(350, 350), sf::Vector2i(rt(rng), 0));
    }
}

void StarField::parallax() {
    // shift stars compensating for player position

    sf::Vector2f delta_p = (c_view->getCenter()-(c_view->getSize()/2.0f)) - last_p; // get the vector of player movement since last frame
    delta_p.y = 0.0f;       // do not compensate for y

    // for each star layer
    for (int l = 0; l < star_layc; l++) {
        for (int i = 0; i < star_layers[l]->getVertexCount();i++) {
            (*star_layers[l])[i].position += delta_p * parallax_c[l];                  // compensate star position based on player movement
        }                                                                              // multiply compensation coeeficient to create different depths                       
    }

    // for each nebula layer
    for (int l = 0; l < nebula_layc; l++) {
        for (int i = 0; i < nebula_layers[l]->getVertexCount();i++) {
            (*nebula_layers[l])[i].position += delta_p * parallax_n_c[l];                  // compensate star position based on player movement
        }
    }

    // update last position
    last_p = c_view->getCenter()-(c_view->getSize()/2.0f);
}

void StarField::draw() {
    // Apply parallax
    parallax();
    
    for (int i = 0; i < nebula_layc; i++) {
        
    }
    // Draw vertex arrays of stars
    for (int i = 0; i < star_layc; i++) {
        m_window->draw(*(star_layers[i]), star_rstate);
        if (i < nebula_layc) {
            // Draw vertex arrays of nebulas in between
            m_window->draw(*(nebula_layers[i]), nebula_rstate);
        }
    }
}