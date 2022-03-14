#pragma once
#include <SFML/Graphics.hpp>

//Implemented by Daniel 03.01 11:23 AM
enum class DIRECTIONS:uint8_t {
	LEFT=0,RIGHT,UP,DOWN
};
//Implemented by Daniel 03.01 11:24 AM
class Entity {
	
protected:
	//variables
	//Added by Daniel 03.01 11:24 AM
	sf::Sprite m_sprite;
	int m_HP=0;
	int m_MaxHP=0;
	float m_Speed=0.0f;
public:
	//Implemented by Daniel 03.01 11:26 AM
	Entity(int health, float speed);
	virtual ~Entity();
	//Implemented by Daniel 03.01 11:28 AM
	//this is called every single frame
	virtual void move(DIRECTIONS dir);
	//Implemented by Daniel 03.01 11:34 AM
	virtual void setTexture(const sf::Texture& texture);
	//Implemented by Daniel 03.05 2:24 PM
	sf::Vector2f getSize();
	//Implemented by Daniel 03.05 2:26 PM
	sf::Vector2f getTopLeftPos();
};

