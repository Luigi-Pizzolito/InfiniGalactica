#include "CameraFollowScroll.h"

void CameraFollowHorzScroll(sf::RenderWindow* window, sf::View* view, const sf::Sprite* sprite) {
    // view->rotate(0.6f);
    // const sf::Vector2f c_pos = view->getCenter() - (view->getSize() / 2.0f); // get camera move offset

    // get the sprite position
    sf::Vector2f s_pos = sprite->getScale();                //first get the sprite texture center, starting by getting the scale
    s_pos.x*=(float)sprite->getTextureRect().width/2.0f;    //then multiply by the texture size
    s_pos.y*=(float)sprite->getTextureRect().height/2.0f;
    s_pos+=sprite->getPosition();                           //then add the sprite position to get sprite center position

    sf::Vector2f view_offset = sf::Vector2f( -sprite->getScale().x*(float)sprite->getTextureRect().width, 0.0f); //x offset by half the player texture width

    sf::Vector2f move = s_pos + view_offset;

    move.y=0.0f;
    view->setCenter(move + (view->getSize() / 2.0f)); //compensate for setCenter instead of setOffset func.
    
    window->setView(*view);
}