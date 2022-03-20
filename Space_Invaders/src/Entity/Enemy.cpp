#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include "MediaManager/SFXPlayer.h"
#include <iostream>
#include "Algorithms/MathUtils.h"
Enemy::Enemy(int health, float speed, const sf::Vector2f& dir, int bullet_count )
	:Entity(health, speed),m_dir(dir),m_shoot_timer(1.0f),m_projectile_texture(nullptr),m_bullets_count(bullet_count)
{
	m_shoot_timer.setDuration(1.0f+ std::rand() / std::numeric_limits<float>().max()) ;
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

EnemyBullet* Enemy::spawnBullet(int bullet_index)
{
	//the basic enemy ignores the index
	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, VectorMath::getAABBMidBack(getCenterPos(), getSize()), VectorMath::Vdirection::LEFT);
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}

//Furtive
Furtive::Furtive(int health, float speed, const sf::Vector2f& dir):
	Enemy(health,speed,dir,3)
{
	m_shoot_timer.setDuration(1.0f + float(std::rand()%(15))/35.0f);
	m_bullets_count = 3;
}

Furtive::~Furtive()
{

}

EnemyBullet* Furtive::spawnBullet()
{
	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, VectorMath::getAABBMidBack(getCenterPos(), getSize()), VectorMath::Vdirection::LEFT);
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}

EnemyBullet* Furtive::spawnBullet(int bullet_index)
{
	//spawn the bullet based on the position of the point in the array
	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, points[bullet_index], VectorMath::Vdirection::LEFT);
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;


}

void Furtive::move()
{
	m_sprite.move(m_dir * m_Speed);
	setPoints();
}

void Furtive::setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)
{
	//set the texture
	m_sprite.setTexture(texture);
	//recenter
	m_sprite.setOrigin(getSize() / 2.0f);
	//set scale
	m_sprite.setScale(scalevec);
	setPoints();
}

void Furtive::setPoints()
{
	//for this enemy
	points[0] = VectorMath::getAABBMidBack(getCenterPos(), getSize());
	points[1] = points[0] - sf::Vector2f(0, getSize().y / 2.0f) * 0.62f;
	points[2] = points[0] + sf::Vector2f(0, getSize().y / 2.0f) * 0.62f;

}
//Attacker

Attacker::Attacker(int health, float speed, const sf::Vector2f& dir, sf::Texture* textures, sf::Vector2f& scalevec)
	:Enemy(health, speed, dir), current_slot(0)
{
	m_shoot_timer.setDuration(1.0f + float(std::rand() % (15)) / 35.0f);
	m_bullets_count = 2;
	m_sprite.setTexture(textures[0]);
	m_sprite.setOrigin(getSize() / 2.0f);
	//set scale
	m_sprite.setScale(scalevec);
	m_textures[0] = textures;
	m_textures[1] = (textures+1);
}

Attacker::~Attacker()
{

}



EnemyBullet* Attacker::spawnBullet(int bullet_index)
{
	//spawn the bullet based on the position of the point in the array
	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, points[bullet_index], VectorMath::Vdirection::LEFT);
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}



bool Attacker::canShoot()
{
	m_shoot_timer.start();
	bool time_out= m_shoot_timer.timeOut();
	if (time_out) { 
		(current_slot == 0) ? current_slot++ : current_slot = 0;
		m_sprite.setTexture(*m_textures[current_slot]);
	}
	return time_out;
}

void Attacker::move()
{
	m_sprite.move(m_dir * m_Speed);
	setPoints();
}

void Attacker::setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)
{
	//basically swapping textures

}

void Attacker::setPoints()
{

	points[0] = VectorMath::getAABBMidBack(getCenterPos(), getSize()) - sf::Vector2f((getSize().x/2.0f)*0.70f, (getSize().y / 2.0f) * 0.62f) ;
	points[1] = VectorMath::getAABBMidBack(getCenterPos(), getSize()) - sf::Vector2f((getSize().x / 2.0f) * 0.70f, -(getSize().y / 2.0f) * 0.62f);

}
