#pragma once
#include <SFML/Graphics.hpp>
//Base
class Projectile {
	
protected:
	sf::Sprite m_sprite;
	int m_damage;
	float m_speed;
	sf::Vector2f m_dir;
	sf::Vector2f m_initpos;
public:
	Projectile(int damage,float speed,const sf::Vector2f& position,const sf::Vector2f& direction);
	virtual ~Projectile();
	virtual void move();
	virtual void rotate(float rotation_speed);
	virtual void setSpeed(float speed);
	void setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec);
	int getDamage() const { return m_damage; }
	const sf::Vector2f getSize()const;
	const sf::Vector2f& getCenterPos()const;
	const sf::Vector2f getTopLeftPos()const;
};

//Player 
class PlayerBullet:public Projectile {
public:
	PlayerBullet(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction);
	~PlayerBullet();
	const sf::Sprite& getSprite()const { return m_sprite; }
};



//Enemy
class EnemyBullet:public Projectile {
public:
	EnemyBullet(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction);
	~EnemyBullet();
	const sf::Sprite& getSprite()const { return m_sprite; }
};

class DeviatedProjectile :public EnemyBullet {
private:
	float m_deviation_angle;
	int iteration_ = 0;
public:
	DeviatedProjectile(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction, float deviation_angle);
	~DeviatedProjectile();
	void move()override;
};
