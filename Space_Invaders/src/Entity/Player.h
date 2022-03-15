#pragma once
#include "PhysicsEntity.h"

//forward Declaration
class Enemy ;
class Item_;
class EnemyBullet;
//class
class Player :public PhysicsEntity {     // Player class is now an extension of the Physics entity class

public:
	Player(int health, float speed, float fric); // Player initialiser also includes a friction parameter now
	~Player();
	float player_speed;
	float player_friction;
	void move(DIRECTIONS dir) override;
	void applyExtForce(sf::Vector2f force);

	//Overloads of Collisions
	void setTexture(const sf::Texture& texture)override;
	bool collidesWith(Enemy* enemy);
	bool collidesWith(EnemyBullet* enemybullet);
	bool collidesWith(Item_* iem);
	const sf::Sprite& getSprite()const { return m_sprite; }
	void hurt(EnemyBullet* bullet);
	int getHP() {return m_HP;}
	int getMaxHP() {return m_MaxHP;}
};
