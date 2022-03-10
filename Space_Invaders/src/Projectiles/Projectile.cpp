#include "Projectile.h"
#include <cmath>
#include <iostream>

//Implemented by Daniel 03.01 3:00 PM
Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_sprite.setPosition(position);
	m_dir = direction;
}

Projectile::~Projectile()
{
	//virtual destructor for polymorphic behavior
}

//Implemented by Daniel 03.01 3:22 PM
void Projectile::move()
{
	m_sprite.move(m_dir * m_speed);
}
//Implemented by Daniel 03.01 3:26 PM
void Projectile::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(0.2f, 0.2f);
}

//Implemented by Daniel 03.01 3:31 PM
PlayerBullet::PlayerBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(position,direction)
{
	m_speed = 20.0f;
	m_damage = 15.0f;
}

PlayerBullet::~PlayerBullet()
{

}

//Implemented by Daniel 03.01 3:46 PM
EnemyBullet::EnemyBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(position, direction)
{
	m_speed = 20.0f;
	m_damage = 15.0f;
}

EnemyBullet::~EnemyBullet()
{

}
