#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include <iostream>
//Implemented by Daniel 03.01 1:03 PM
Enemy::Enemy(int health, float speed, const sf::Vector2f& dir)
	:Entity(health, speed),m_dir(dir),m_shoot_timer(1.0f)
{
	
}

Enemy::~Enemy()
{

}
//Implemented by Daniel 03.01 1:12 PM
void Enemy::move()
{
	m_sprite.move(m_dir*m_Speed);
}
//Implemented by Daniel 03.02 2:47 PM
void Enemy::rotate(float angle)
{
	m_sprite.setRotation(angle);

}
//Implemented by Daniel 03.01 1:17 PM
void Enemy::setTexture(const sf::Texture& texture)
{
	m_sprite.setScale(0.5, 0.5f);
	m_sprite.setTexture(texture);
	
}
//Implemented by Daniel 03.05 1:20 PM
void Enemy::setPosition(const sf::Vector2f& position)
{
	
	m_sprite.setPosition(position.x, rand() % static_cast<int>(position.y- m_sprite.getTextureRect().height * m_sprite.getScale().y));

}
//Implemented by Daniel 03.06 4:01 PM
bool Enemy::canShoot()
{
	m_shoot_timer.start();
	return m_shoot_timer.timeOut();
}
//Implemented by Daniel 03.01 1:28 PM
bool Enemy::collidesWith(const PlayerBullet* bullet)
{
	return m_sprite.getGlobalBounds().intersects(bullet->getSprite().getGlobalBounds());
}
//Implemented by Daniel 03.05 6:02 PM
void Enemy::hurt(PlayerBullet* bullet)
{
	m_HP -= bullet->getDamage();
}
//Implemented by Daniel 03.05 6:04 PM
int Enemy::getHP()
{
	return m_HP;
}
