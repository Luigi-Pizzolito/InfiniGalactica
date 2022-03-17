#include "Projectile.h"
#include "MediaManager/SFXPlayer.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_initpos = position;
	//m_sprite.setPosition(position);
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
	m_sprite.setOrigin(getSize() / 2.0f);
	m_sprite.setPosition(m_initpos);
	m_sprite.setScale(0.2f, 0.2f);
}

const sf::Vector2f Projectile::getSize() const
{
	return sf::Vector2f(m_sprite.getTextureRect().width * m_sprite.getScale().x, m_sprite.getTextureRect().height * m_sprite.getScale().y);
}

const sf::Vector2f& Projectile::getTopLeftPos() const
{
	return m_sprite.getPosition();
}

PlayerBullet::PlayerBullet(const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(position,direction)
{
	m_speed = 20.0f;
	m_damage = 20.0f;
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
