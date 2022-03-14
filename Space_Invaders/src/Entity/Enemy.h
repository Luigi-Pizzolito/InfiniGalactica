#pragma once
#include "Entity.h"
#include "Algorithms/Utilities.h"
class PlayerBullet;
//class
class Enemy :public Entity {
protected:
	sf::Vector2f m_dir;
	Control::GameTimer m_shoot_timer;
public:
	Enemy(int health, float speed, const sf::Vector2f& dir);
	~Enemy();
	void move();
	void rotate(float angle);
	void setTexture(const sf::Texture& texture)override;
	void setPosition(const sf::Vector2f& position);
	bool canShoot();
	//Overloads of Collisions
	bool collidesWith(const PlayerBullet* bullet);
	const sf::Sprite& getSprite()const { return m_sprite; }
	void hurt(const PlayerBullet* bullet);
	int getHP();
};
