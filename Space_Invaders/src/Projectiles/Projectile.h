#pragma once
#include <SFML/Graphics.hpp>

//Class Implemented by Daniel 03.01 3:00 PM
class Projectile {
	
protected:
	//Implemented by Daniel 03.01 3:00 PM
	sf::Sprite m_sprite;
	sf::Texture* m_texture;
	int m_damage;
	float m_speed;
	sf::Vector2f m_dir;
public:
	//Implemented by Daniel 03.01 3:10 PM
	Projectile(const sf::Vector2f& position,const sf::Vector2f& direction);
	virtual ~Projectile();
	//Implemented by Daniel 03.01 3:20 PM
	void move();
	//Implemented by Daniel 03.01 3:25 PM
	void setTexture(const sf::Texture& texture);
	//Implemented by Daniel 03.01 3:27 PM
	int getDamage() { return m_damage; }
};


//Class Implemented by Daniel 03.01 3:27 PM
class PlayerBullet:public Projectile {
public:
	//Implemented by Daniel 03.01 3:30 PM
	PlayerBullet(const sf::Vector2f& position,const sf::Vector2f& direction);
	~PlayerBullet();
	//Implemented by Daniel 03.01 3:35 PM
	const sf::Sprite& getSprite()const { return m_sprite; }
};
//Class Implemented by Daniel 03.01 3:40 PM
class EnemyBullet:public Projectile {
public:
	//Implemented by Daniel 03.01 3:45 PM
	EnemyBullet(const sf::Vector2f& position, const sf::Vector2f& direction);
	~EnemyBullet();
	//Implemented by Daniel 03.01 3:47 PM
	const sf::Sprite& getSprite()const { return m_sprite; }
};
