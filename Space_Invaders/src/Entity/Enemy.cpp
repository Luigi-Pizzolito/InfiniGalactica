#include "Enemy.h"
#include "Projectiles/Projectile.h"

Enemy::Enemy(int health, float speed)
	:Entity(health, speed)
{
	
}

Enemy::~Enemy()
{

}

void Enemy::move(DIRECTIONS dir)
{

}

void Enemy::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

void Enemy::shoot()
{

}

bool Enemy::collidesWith(const PlayerBullet& bullet)
{
	return m_sprite.getGlobalBounds().intersects(bullet.getSprite().getGlobalBounds());
}
