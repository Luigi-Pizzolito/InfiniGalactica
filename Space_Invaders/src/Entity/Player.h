#pragma once
#include "PhysicsEntity.h"
#include "Algorithms/Utilities.h"
//forward Declaration
class Enemy ;
class GameItem;
class EnemyBullet;
namespace Control { class GameTimer;}
//class
class Player :public PhysicsEntity {     // Player class is now an extension of the Physics entity class
protected:
	//Base stats for bullets
	int m_bullet_damage;
	float m_bullet_speed;
	bool m_centered=false;

	//base stats for upgrades
	int b_m_HP;
	int b_m_MaxHP;
	int b_m_bullet_damage;
	float b_m_bullet_speed;
public:
	Player(int health, float speed, float fric); // Player initialiser also includes a friction parameter now
	~Player();
	float player_speed;
	float player_friction;
	void setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)override;
	void setTexture(const sf::Texture& texture);
	void move(DIRECTIONS dir) override;
	void applyExtForce(sf::Vector2f force);
	Control::GameTimer player_bullet_timer;
	//Overloads of Collisions
	bool collidesWith(Enemy* enemy);
	bool collidesWith(EnemyBullet* enemybullet);
	bool collidesWith(GameItem* item_);
	const sf::Sprite& getSprite()const { return m_sprite; }
	void hurt(EnemyBullet* bullet);
	int getHP() {return m_HP;}
	int getMaxHP() {return m_MaxHP;}
	bool canShoot();
	//Buffs
	void upgrade(int upgrade_lvl);
	void upgradeHP(int upgrade_lvl);
	void heal(float quantity);
	void boostFireRate(float percent_increment);
	void increaseBulletDamage(float increment);
	void increaseBulletSpeed(float increment);
	int getBulletDamage() { return m_bullet_damage; }
	float getBulletSpeed() { return m_bullet_speed; }
};
