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
	int m_bullets_count ;
public:
	Enemy(int health, float speed, const sf::Vector2f& dir,int bullet_count=1);
	~Enemy();
	virtual void move();
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
	virtual EnemyBullet* spawnBullet();
	virtual EnemyBullet* spawnBullet(int bullet_index);
	virtual bool canShoot();
	void setBulletParameters(uint8_t bullet_damage, uint8_t bullet_speed);
	int getBulletsCount() { return m_bullets_count; }
};

class Furtive :public Enemy {
protected:
	sf::Vector2f points[3];

public:
	Furtive(int health, float speed, const sf::Vector2f& dir);
	~Furtive();
	EnemyBullet* spawnBullet()override;
	EnemyBullet* spawnBullet(int bullet_index)override;
	void move()override;
	void setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)override;
	
protected:
	void setPoints();
};

class Attacker :public Enemy {
protected:
	sf::Vector2f points[2];
	sf::Texture* m_textures[2];
	bool m_ready=false;
	Control::GameTimer bullet_timer;
	uint8_t current_slot;
public:
	Attacker(int health, float speed, const sf::Vector2f& dir,sf::Texture* textures,sf::Vector2f& scalevec);
	~Attacker();

	EnemyBullet* spawnBullet(int bullet_index)override;
	bool canShoot()override;
	void move()override;
	void setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)override;
	
protected:
	void setPoints();

};
