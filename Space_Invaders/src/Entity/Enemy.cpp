#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include <iostream>
Enemy::Enemy(int health, float speed, const sf::Vector2f& dir)
	:Entity(health, speed),m_dir(dir),m_shoot_timer(1.0f)
{
	//std::cout << "Enemy created\n";
}

Enemy::~Enemy()
{
	std::cout << "Enemy destroyed\n";
}
void Enemy::move()
{
	m_sprite.move(m_dir*m_Speed);
}
void Enemy::rotate(float angle)
{
	m_sprite.setRotation(angle);

}
void Enemy::setTexture(const sf::Texture& texture)
{
	m_sprite.setScale(0.4, 0.4f);
	m_sprite.setTexture(texture);
	
}
void Enemy::setPosition(const sf::Vector2f& position)
{
	//m_sprite.setPosition(position.x, rand() % static_cast<int>(position.y - m_sprite.getTextureRect().height * m_sprite.getScale().y));

	m_sprite.setPosition(position.x, rand() % static_cast<int>(position.y- getSize().y));

}
bool Enemy::canShoot()
{
	m_shoot_timer.start();
	return m_shoot_timer.timeOut();
}
bool Enemy::collidesWith(const PlayerBullet* bullet)
{
	return m_sprite.getGlobalBounds().intersects(bullet->getSprite().getGlobalBounds());
}
void Enemy::hurt(const PlayerBullet* bullet)
{
	m_HP -= bullet->getDamage();
}
int Enemy::getHP()
{
	return m_HP;
}
