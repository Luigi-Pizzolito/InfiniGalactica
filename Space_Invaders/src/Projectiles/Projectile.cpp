#include "Projectile.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_sprite.setPosition(position);
	m_dir = direction;
}

Projectile::~Projectile()
{
	//virtual destructor for polymorphic behavior
}

void Projectile::move()
{
	m_sprite.move(m_dir * m_speed);
}
void Projectile::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(0.2f, 0.2f);
}

PlayerBullet::PlayerBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(position,direction)
{
	m_speed = 20.0f;
	m_damage = 15.0f;
}

PlayerBullet::~PlayerBullet()
{

}

EnemyBullet::EnemyBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(position, direction)
{
	m_speed = 20.0f;
	m_damage = 15.0f;
}

EnemyBullet::~EnemyBullet()
{

}
