#pragma once
class Projectile {
	
protected:

	sf::Sprite m_sprite;
	sf::Texture* m_texture;
	int m_damage;
	float m_speed;
public:
	Projectile(sf::Vector2f position,sf::Vector2f direction);
	virtual ~Projectile();
	virtual void move(const sf::Vector2f& dir);
	virtual void setTexture(const sf::Texture& texture);

};

class PlayerBullet:public Projectile {
public:
	PlayerBullet(sf::Vector2f position, sf::Vector2f direction);
	~PlayerBullet();
	const sf::Sprite& getSprite()const { return m_sprite; }
};

class EnemyBullet:public Projectile {
public:
	EnemyBullet(sf::Vector2f position, sf::Vector2f direction);
	~EnemyBullet();
	const sf::Sprite& getSprite()const { return m_sprite; }
};