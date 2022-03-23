#include "Projectile.h"
#include "MediaManager/SFXPlayer.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction)
	:m_initpos(position),m_dir(direction),m_speed(speed),m_damage(damage)
{}

Projectile::~Projectile()
{}

void Projectile::move()
{
	m_sprite.move(m_dir * m_speed);
}
void Projectile::setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(getSize() / 2.0f);
	m_sprite.setPosition(m_initpos);
	m_sprite.setScale(scalevec);
}

const sf::Vector2f Projectile::getSize() const
{
	return sf::Vector2f(m_sprite.getTextureRect().width * m_sprite.getScale().x, m_sprite.getTextureRect().height * m_sprite.getScale().y);
}

const sf::Vector2f& Projectile::getCenterPos() const
{
	return m_sprite.getPosition();
}

const sf::Vector2f Projectile::getTopLeftPos()const
{
	return(getCenterPos() - getSize() / 2.0f);
}

PlayerBullet::PlayerBullet(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(damage,speed,position,direction)
{
	
}

PlayerBullet::~PlayerBullet()
{
	
}

EnemyBullet::EnemyBullet(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction)
	:Projectile(damage, speed, position, direction)
{}

EnemyBullet::~EnemyBullet()
{
	// std::cout << "Destroyed" << std::endl;
}

DeviatedProjectile::DeviatedProjectile(int damage, float speed, const sf::Vector2f& position, const sf::Vector2f& direction,float deviation_angle)
	:EnemyBullet(damage,speed,position,direction),m_deviation_angle(deviation_angle)
{
	
}

DeviatedProjectile::~DeviatedProjectile()
{

}

void DeviatedProjectile::move()
{
	//std::cout << m_deviation_angle << std::endl;
	m_sprite.rotate(m_deviation_angle/20.0f);
	sf::Transform rot_matrix;
	rot_matrix.rotate(m_deviation_angle/20.0f);
	if (m_deviation_angle != 0) {

			}
	m_dir=rot_matrix.transformPoint(m_dir);
	iteration_++;
	m_sprite.move(m_dir * m_speed);
	
}
