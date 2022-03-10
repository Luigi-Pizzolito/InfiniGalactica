#include "CameraFollowScroll.h"
#include <cmath>
// #include <iostream>
// Class Implemented by Luigi 04.03 14:02

CameraFollowHorzScroll::CameraFollowHorzScroll(sf::RenderWindow* window, sf::View* view, Player* player, sf::Vector2f c_speed):window(window),view(view),player(player),c_speed(c_speed) {
    const sf::Sprite* sprite = &player->getSprite();
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

//Implemented by Luigi with modifications 05.03 16:34
void CameraFollowHorzScroll::follow() {
    //Implemented player bounds keeping by Luigi 05.03 19:17
    // check if player is going out of bounds
    float border_width = 2.0f;
    float repulse_force = 0.5f;
    sf::FloatRect player_bounds = player->getSprite().getGlobalBounds();
    sf::FloatRect view_bounds( view->getCenter()-(view->getSize()/2.0f) + sf::Vector2f(border_width, border_width) , view->getSize() + sf::Vector2f(-border_width, -border_width) );
    // std::cout << player_bounds.left << "," << player_bounds.top << "," << player_bounds.width << "," << player_bounds.height << "\n";
    // std::cout << view_bounds.left   << "," << view_bounds.top   << "," << view_bounds.width   << "," << view_bounds.height   << "\n\n";
    //out of bounds top
    if ( player_bounds.top <= view_bounds.top ) {
        if ((player->getAccel())->y < 0) {*(player->getAccel()) = sf::Vector2f((player->getAccel())->x, 0.0f);}
        player->applyExtForce(sf::Vector2f(0.0f, 1.5f*repulse_force));
    }
    //out of bounds bottom
    else if ( player_bounds.top + player_bounds.height >= view_bounds.top + view_bounds.height) {
        if ((player->getAccel())->y > 0) {*(player->getAccel()) = sf::Vector2f((player->getAccel())->x, 0.0f);}
        player->applyExtForce(sf::Vector2f(0.0f, -1.5f*repulse_force));
    }
    //out of bounds left
    if ( player_bounds.left <= view_bounds.left ) {
        if ((player->getAccel())->x < 0) {*(player->getAccel()) = sf::Vector2f(0.0f, (player->getAccel())->y);}
        player->applyExtForce(sf::Vector2f(1.5f*repulse_force, 0.0f));
    }
    //out of bounds right
    else if ( player_bounds.left + player_bounds.width >= view_bounds.left + view_bounds.width) {
        if ((player->getAccel())->x > 0) {*(player->getAccel()) = sf::Vector2f(0.0f, (player->getAccel())->y);}
        player->applyExtForce(sf::Vector2f(-repulse_force, 0.0f));
    }

    // Get the vector the camera should move in
    sf::Vector2f move = last_p + c_speed/60.0f;

    // Implemented player push camera by Luigi 07.03 11:55
    // Get the position of the player, if in the last band to the right of the screen, move the camera extra in proportion to the player position and curent player speed
    // aka. player pushes the camera.
    const sf::Sprite* sprite = &player->getSprite();
    const float player_x = sprite->getPosition().x+((float)sprite->getTextureRect().width/2.0f);
    const float push_boundary = view->getCenter().x+(view->getSize().x/2.5f); // band size defined here
    if ( player_x >= push_boundary) {
        float player_push = ((sprite->getPosition() - p_last_p)).x;
        float c_border =  player_x/(view->getSize().x+last_p.x);
        // relation to camera push amount
        float c_push = 0.5f + (c_border*c_border*c_border/5.5f);
        // std::cout << c_push << "\n";
        // only push the camera forwards in x direction.
        move.x += (player_push > 0) ? player_push*c_push : 0;
    }


    view->setCenter(move + (view->getSize() / 2.0f)); //compensate for setCenter instead of setOffset func.
    window->setView(*view);
    last_p = view->getCenter() - (view->getSize() / 2.0f);
    p_last_p = sprite->getPosition();
    p_last_p.y = 0;
}