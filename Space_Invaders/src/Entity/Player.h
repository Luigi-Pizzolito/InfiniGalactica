#pragma once
#include "Entity.h"

//forward Declaration
class Enemy ;
class Item_;
class EnemyBullet;
//class
class Player :public Entity {

private:
	float accel_x;
	float speed_x;
	float accel_y;
	float speed_y;

public:

	Player(int health, float speed);
	~Player();
	void move(DIRECTIONS dir) override;
	void shoot();
	void physics();
	//Overloads of Collisions
	void setTexture(const sf::Texture& texture)override;
	bool collidesWith(const Enemy& enemy);
	bool collidesWith(const EnemyBullet& enemybullet);
	bool collidesWith(const Item_& iem);
	const sf::Sprite& getSprite()const { return m_sprite; }

};