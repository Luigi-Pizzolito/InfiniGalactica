#include "CameraFollowScroll.h"
#include <cmath>
#include <iostream>


CameraFollowHorzScroll::CameraFollowHorzScroll(sf::RenderWindow* window, sf::View* view, const Player* player):window(window),view(view),player(player) {

}

CameraFollowHorzScroll::~CameraFollowHorzScroll() {}

float CameraFollowHorzScroll::mapF(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void CameraFollowHorzScroll::follow() {
    // view->rotate(0.6f);
    // const sf::Vector2f c_pos = view->getCenter() - (view->getSize() / 2.0f); // get camera move offset
    const sf::Sprite* sprite = &(*player).getSprite();
    // get the sprite position
    sf::Vector2f s_pos = sprite->getScale();                //first get the sprite texture center, starting by getting the scale
    s_pos.x*=(float)sprite->getTextureRect().width/2.0f;    //then multiply by the texture size
    s_pos.y*=(float)sprite->getTextureRect().height/2.0f;
    s_pos+=sprite->getPosition();                           //then add the sprite position to get sprite center position

    // get player movement
    sf::Vector2f delta_p = sprite->getPosition() - last_p; // get the vector of player movement since last frame
    float max_player_x_speed = std::sqrt(player->player_speed*player->player_friction);
    std::cout << std::pow(delta_p.x, 0.5f) << "/" << std::pow(max_player_x_speed, 0.5f) <<"\n";
    float sprite_width = sprite->getScale().x*(float)sprite->getTextureRect().width;
    float x_offset = mapF(std::pow(delta_p.x, 0.5f), 0.0f, std::pow(max_player_x_speed, 0.5f), -sprite_width, -view->getSize().x+2*sprite_width);
    sf::Vector2f view_offset  = sf::Vector2f( x_offset, 0.0f); //x offset by half the player texture width
    // update last position
    last_p = sprite->getPosition();

    sf::Vector2f move = s_pos + view_offset;

    move.y=0.0f;
    view->setCenter(move + (view->getSize() / 2.0f)); //compensate for setCenter instead of setOffset func.
    
    window->setView(*view);
}