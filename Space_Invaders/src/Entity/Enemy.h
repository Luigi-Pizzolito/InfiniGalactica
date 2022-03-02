#pragma once
#include "Entity.h"

class PlayerBullet;
//class
class Enemy :public Entity {

public:
	Enemy(int health, float speed);
	~Enemy();
	void move(DIRECTIONS dir) override;
	void setTexture(const sf::Texture& texture)override;
	void shoot();
	//Overloads of Collisions
	bool collidesWith(const PlayerBullet& bullet);
	const sf::Sprite& getSprite()const { return m_sprite; }
};