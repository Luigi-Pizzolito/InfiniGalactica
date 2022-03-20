#pragma once
#include <SFML/Graphics.hpp>

enum class DIRECTIONS:uint8_t {
	LEFT=0,RIGHT,UP,DOWN
};
class Entity {
	
protected:
	//variables
	sf::Sprite m_sprite;
	int m_HP=0;
	int m_MaxHP=0;
	float m_Speed=0.0f;
public:
	Entity(int health, float speed);
	virtual ~Entity();
	//this is called every single frame
	virtual void move(DIRECTIONS dir);
	virtual void setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec);
	const sf::Vector2f getSize()const;
	const sf::Vector2f getTopLeftPos()const;
	const sf::Vector2f& getCenterPos()const;
};

