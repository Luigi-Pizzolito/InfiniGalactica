#include "CameraFollowScroll.h"
#include <cmath>
#include <iostream>


CameraFollowHorzScroll::CameraFollowHorzScroll(sf::RenderWindow* window, sf::View* view, const Player* player, sf::Vector2f c_speed):window(window),view(view),player(player),c_speed(c_speed) {
    const sf::Sprite* sprite = &(*player).getSprite();
    // get the player sprite position
    sf::Vector2f s_pos = sprite->getScale();                //first get the sprite texture center, starting by getting the scale
    s_pos.x*=(float)sprite->getTextureRect().width/2.0f;    //then multiply by the texture size
    s_pos.y*=(float)sprite->getTextureRect().height/2.0f;
    s_pos+=sprite->getPosition();                           //then add the sprite position to get sprite center position
    float sprite_width = sprite->getScale().x*(float)sprite->getTextureRect().width;
    sf::Vector2f view_offset  = sf::Vector2f( -sprite_width, 0.0f); //x offset by half the player texture width
    last_p = s_pos + view_offset;

    view->setCenter(last_p + (view->getSize() / 2.0f)); //compensate for setCenter instead of setOffset func.
    window->setView(*view);
}

CameraFollowHorzScroll::~CameraFollowHorzScroll() {}

float CameraFollowHorzScroll::mapF(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void CameraFollowHorzScroll::follow() {
    // view->rotate(0.6f);
    // const sf::Vector2f c_pos = view->getCenter() - (view->getSize() / 2.0f); // get camera move offset
    

    // get player movement
    // sf::Vector2f delta_p = sprite->getPosition() - last_p; // get the vector of player movement since last frame
    // float max_player_x_speed = std::sqrt(player->player_speed*player->player_friction);
    // std::cout << std::pow(delta_p.x, 0.5f) << "/" << std::pow(max_player_x_speed, 0.5f) <<"\n";
    
    // float x_offset = mapF(std::pow(delta_p.x, 0.5f), 0.0f, std::pow(max_player_x_speed, 0.5f), -sprite_width, -view->getSize().x+2*sprite_width);
    
    // update last position
    // last_p = sprite->getPosition();

    // check if player is going out of bounds


    sf::Vector2f move = last_p + c_speed/60.0f;
    view->setCenter(move + (view->getSize() / 2.0f)); //compensate for setCenter instead of setOffset func.
    window->setView(*view);
    last_p = view->getCenter() - (view->getSize() / 2.0f);
}