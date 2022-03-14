#pragma once
#include "Entity.h"
#include "Algorithms/Utilities.h"
class PlayerBullet;
//class
class Enemy :public Entity {
protected:
	//Implemented by Daniel 03.01 1:01 PM
	sf::Vector2f m_dir;
	Control::GameTimer m_shoot_timer;
public:
	//Implemented by Daniel 03.01 1:02 PM
	Enemy(int health, float speed, const sf::Vector2f& dir);
	~Enemy();
	//Implemented by Daniel 03.01 1:10 PM
	void move();
	//Implemented by Daniel 03.02 2:45 PM
	void rotate(float angle);
	//Implemented by Daniel 03.01 1:17 PM
	void setTexture(const sf::Texture& texture)override;
	//Implemented by Daniel 03.05 1:20 PM
	void setPosition(const sf::Vector2f& position);
	//Implemented by Daniel 03.06 4:00 PM
	bool canShoot();
	//Implemented by Daniel 03.01 1:27 PM
	//Overloads of Collisions
	bool collidesWith(const PlayerBullet* bullet);
	//Implemented by Daniel 03.01 1:29 PM
	const sf::Sprite& getSprite()const { return m_sprite; }
	//Implemented by Daniel 03.05 6:00 PM
	void hurt(const PlayerBullet* bullet);
	//Implemented by Daniel 03.05 6:03 PM
	int getHP();
};
