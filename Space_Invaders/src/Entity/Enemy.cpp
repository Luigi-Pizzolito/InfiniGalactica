#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include <iostream>
Enemy::Enemy(int health, float speed, const sf::Vector2f& dir)
	:Entity(health, speed),m_dir(dir)
{
	//calculate the position
	

	
}

Enemy::~Enemy()
{

}

void Enemy::move()
{
	m_sprite.move(m_dir*m_Speed);
}

void Enemy::rotate(float angle)
{
	m_sprite.setRotation(angle);
	//std::cout << m_sprite.getRotation() << std::endl;
}

void Enemy::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(0.5f, 0.5f);
	
}

void Enemy::setPosition(const sf::Vector2f& position)
{
	
	m_sprite.setPosition(position.x, rand() % static_cast<int>(position.y- m_sprite.getTextureRect().height * m_sprite.getScale().y));

}

void Enemy::shoot()
{
	//must  call the spawn enemy bullet function in the basic shooter .cpp

}

bool Enemy::collidesWith(const PlayerBullet* bullet)
{
	return m_sprite.getGlobalBounds().intersects(bullet->getSprite().getGlobalBounds());
}
