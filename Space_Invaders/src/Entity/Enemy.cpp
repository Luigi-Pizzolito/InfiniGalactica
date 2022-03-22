#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include "MediaManager/SFXPlayer.h"
#include <iostream>
#include "Algorithms/MathUtils.h"
#include "SceneManager/Scene.h"
Enemy::Enemy(int health, float speed, const sf::Vector2f& dir, int bullet_count )
	:Entity(health, speed),m_dir(dir),m_projectile_texture(nullptr),m_bullets_count(bullet_count)
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
	m_sprite.setPosition(position);
}

void Enemy::setPosition(float x_pos)
{
	//todo: also randomise x postion from x.position to x.position + 0.5 to 1.0 * screen width
	m_sprite.setPosition(x_pos, rand() % static_cast<int>( SceneManagement::Scene::s_view->getSize().y- getSize().y) + getSize().y / 2.0f);

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
		if (current_slot==0) SFX::play(SFXlib::BulletReload, 40.0f);
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





Starminator::Starminator(int health, float speed, float rotation_speed, const sf::Vector2f& dir)
	:Enemy(health,speed,dir,4),m_textures(nullptr),m_rotation_angle(rotation_speed),m_iteration(2)
{
	m_shoot_timer.setDuration(0.5f + std::rand() / std::numeric_limits<float>().max());

}

Starminator::~Starminator()
{

}

EnemyBullet* Starminator::spawnBullet(int bullet_index)
{
	//spawn the bullet based on the position of the point in the array

	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed,getCenterPos()+ points[bullet_index], VectorMath::getUnitaryVector(points[bullet_index]));
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}

void Starminator::move()
{

	m_sprite.move(m_dir * m_Speed);
	m_sprite.rotate(m_rotation_angle);
	setPoints();


}


void Starminator::setPoints()
{
	sf::Transform trans_format;
	trans_format.rotate(m_rotation_angle*(m_iteration));
	//set the points 
	//left-right
	points[0] =sf::Vector2f(-getSize().x / 2.0f, 0.0f);
	points[1] = sf::Vector2f(+getSize().x / 2.0f, 0.0f);
	//up-down
	points[2] = sf::Vector2f(0.0f , -getSize().y/2.0f);
	points[3]= sf::Vector2f(0.0f, getSize().y / 2.0f);
	if (m_rotation_angle > 0) {
		//create a transformation matrix

		for (uint8_t i = 0; i < m_bullets_count; i++) {
			points[i] = trans_format.transformPoint(points[i]);
		}
		m_iteration++;
	}

}

//Spinner
Spinner::Spinner(int health, float speed, float rotation_speed, const sf::Vector2f& dir)
	:Enemy(health, speed, dir, 1), m_rotation_angle(rotation_speed),m_target_pos_dir(sf::Vector2f(0.0f,0.0f))
{
	m_shoot_timer.setDuration(1.5f + std::rand() / std::numeric_limits<float>().max());
}

Spinner::~Spinner()
{

}
void Spinner::lookAt(const sf::Vector2f& target_pos)
{
	//gets a unitary vector pointing to the players center
	m_target_pos_dir = VectorMath::getUnitaryVector(getCenterPos(), target_pos);
}

void Spinner::move()
{
	m_sprite.rotate(m_rotation_angle);
	m_sprite.move(m_dir * m_Speed);
}

void Spinner::idle()
{
	m_sprite.rotate(m_rotation_angle);
}

EnemyBullet* Spinner::spawnBullet(int bullet_index)
{

	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, getCenterPos(),m_target_pos_dir);
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}

