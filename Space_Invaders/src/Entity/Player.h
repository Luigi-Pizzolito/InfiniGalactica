#pragma once
#include "PhysicsEntity.h"

//Implemented by Daniel 03.01 11:50 AM
//forward Declaration
class Enemy ;
class Item_;
class EnemyBullet;
//class
class Player :public PhysicsEntity {     // Player class is now an extension of the Physics entity class

public:
	//Implemented by Daniel 03.01 11:55 AM
	Player(int health, float speed, float fric); // Player initialiser also includes a friction parameter now
	~Player();
	float player_speed;
	float player_friction;
	//Implemented by Daniel 03.01 11:58 AM
	void move(DIRECTIONS dir) override;
	void shoot();
	//Implemented by Luigi set time!!!!!!!!!!!!!!!!!!!
	void applyExtForce(sf::Vector2f force);

	//Implemented by Daniel 03.01 12:00 PM
	//Overloads of Collisions
	void setTexture(const sf::Texture& texture)override;
	//Implemented by Daniel 03.01 12:12 PM
	bool collidesWith(Enemy* enemy);
	//Implemented by Daniel 03.01 12:15 PM
	bool collidesWith(EnemyBullet* enemybullet);
	//Implemented by Daniel 03.01 12:17 PM
	bool collidesWith(Item_* iem);
	//Implemented by Daniel 03.01 12:22 PM
	const sf::Sprite& getSprite()const { return m_sprite; }
	//Implemented by Daniel 03.05 3:00 PM
	void hurt(EnemyBullet* bullet);
	//Implemented by Daniel 03.05 3:10 PM
	int getHP();
};
