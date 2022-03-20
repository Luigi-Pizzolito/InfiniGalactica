#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include "MediaManager/SFXPlayer.h"
#include <iostream>
#include "Algorithms/MathUtils.h"
Enemy::Enemy(int health, float speed, const sf::Vector2f& dir)
	:Entity(health, speed),m_dir(dir),m_shoot_timer(1.0f),m_projectile_texture(nullptr)
{

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

}

void Enemy::setProjectileTexture(sf::Texture& texture,const sf::Vector2f& scalevec) {
	m_projectile_texture = &texture;
	m_projectile_scale = scalevec;
}

void Enemy::setBulletParameters(uint8_t bullet_damage, uint8_t bullet_speed)
{
	m_bullet_damage = bullet_damage;
	m_bullet_speed = bullet_speed;
}

void Enemy::setPosition(const sf::Vector2f& position)
{
	//m_sprite.setPosition(position.x, rand() % static_cast<int>(position.y - m_sprite.getTextureRect().height * m_sprite.getScale().y));

	m_sprite.setPosition(position.x, rand() % static_cast<int>(position.y- getSize().y)+getSize().y/2.0f);

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
	SFX::play(SFXlib::BulletHit);
}
int Enemy::getHP()
{
	return m_HP;
}

EnemyBullet* Enemy::spawnBullet()
{
	
	EnemyBullet* bullet= new EnemyBullet(m_bullet_damage,m_bullet_speed,VectorMath::getAABBMidBack(getCenterPos(), getSize()), VectorMath::Vdirection::LEFT);
	bullet->setTexture(*m_projectile_texture,m_projectile_scale);
	return bullet;
}
