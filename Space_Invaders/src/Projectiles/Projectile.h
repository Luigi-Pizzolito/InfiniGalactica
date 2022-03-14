#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
	
protected:
	sf::Sprite m_sprite;
	int m_damage;
	float m_speed;
	sf::Vector2f m_dir;
public:
	Projectile(const sf::Vector2f& position,const sf::Vector2f& direction);
	virtual ~Projectile();
	void move();
	void setTexture(const sf::Texture& texture);
	int getDamage() const { return m_damage; }
};


class PlayerBullet:public Projectile {
public:
	PlayerBullet(const sf::Vector2f& position,const sf::Vector2f& direction);
	~PlayerBullet();
	const sf::Sprite& getSprite()const { return m_sprite; }
};
class EnemyBullet:public Projectile {
public:
	EnemyBullet(const sf::Vector2f& position, const sf::Vector2f& direction);
	~EnemyBullet();
	const sf::Sprite& getSprite()const { return m_sprite; }
};
