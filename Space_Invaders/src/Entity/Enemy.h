#pragma once
#include "Entity.h"
#include "Algorithms/Utilities.h"
class PlayerBullet;
class EnemyBullet;
//class
class Enemy :public Entity {
protected:
	sf::Vector2f m_dir;
	sf::Texture* m_projectile_texture;
	Control::GameTimer m_shoot_timer;

	//Enemy stats
	EnemyBullet* bullet;
	//Note , when we create different bullets, they should know their texture
public:
	Enemy(int health, float speed, const sf::Vector2f& dir);
	~Enemy();
	void move();
	void rotate(float angle);
	void setTexture(const sf::Texture& texture)override;
	void setProjectileTexture(sf::Texture& texture);
	void setPosition(const sf::Vector2f& position);
	bool canShoot();
	//Overloads of Collisions
	bool collidesWith(const PlayerBullet* bullet);
	const sf::Sprite& getSprite()const { return m_sprite; }
	sf::Sprite& setSprite() { return m_sprite; }
	void hurt(const PlayerBullet* bullet);
	int getHP();
	EnemyBullet* spawnBullet();
};
