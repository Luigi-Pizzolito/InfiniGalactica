#pragma once
#include "PhysicsEntity.h"
// #include "Physics.h"

//forward Declaration
class Enemy ;
class Item_;
class EnemyBullet;
//class
class Player :public PhysicsEntity {

public:

	Player(int health, float speed, float fric);
	~Player();
	void move(DIRECTIONS dir) override;
	void shoot();

	//Overloads of Collisions
	void setTexture(const sf::Texture& texture)override;
	bool collidesWith(const Enemy& enemy);
	bool collidesWith(const EnemyBullet& enemybullet);
	bool collidesWith(const Item_& iem);
	const sf::Sprite& getSprite()const { return m_sprite; }

};