#pragma once
#include "Entity.h"
#include "Algorithms/Utilities.h"
class PlayerBullet;
class EnemyBullet;
//class
class Enemy :public Entity {
protected:
	//own members
	sf::Vector2f m_dir;
	Control::GameTimer m_shoot_timer;

	//bullet members
	sf::Texture* m_projectile_texture;
	sf::Vector2f m_projectile_scale;
	uint8_t m_bullet_damage;
	uint8_t m_bullet_speed;
	EnemyBullet* bullet;
public:
	Enemy(int health, float speed, const sf::Vector2f& dir);
	~Enemy();
	void move();
	void rotate(float angle);
	void setProjectileTexture(sf::Texture& texture, const sf::Vector2f& scalevec);
	void setPosition(const sf::Vector2f& position);
	const sf::Sprite& getSprite()const { return m_sprite; }
	sf::Sprite& setSprite() { return m_sprite; }

	//Overloads of Collisions
	bool collidesWith(const PlayerBullet* bullet);
	void hurt(const PlayerBullet* bullet);
	int getHP();

	//bullet related methods
	EnemyBullet* spawnBullet();
	bool canShoot();
	void setBulletParameters(uint8_t bullet_damage, uint8_t bullet_speed);
};
