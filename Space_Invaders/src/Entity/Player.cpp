#include "Player.h"
#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include <cmath>

Player::Player(int health, float speed):Entity(health,speed)
{
	accel_x = 0.0f;
	speed_x = 0.0f;
	accel_y = 0.0f;
	speed_y = 0.0f;
}

Player::~Player()
{

}

void Player::move(DIRECTIONS dir)
{
	//A player and Enemy version of the function was created just in case we want to add
	//items with effects that will change the speed of the player
	switch (dir)
	{
	case DIRECTIONS::LEFT:
		// m_sprite.move(-m_Speed, 0.0f);
		accel_x=-m_Speed/50.0f;
		break;
	case DIRECTIONS::RIGHT:
		// m_sprite.move(m_Speed, 0.0f);
		accel_x=m_Speed/50.0f;
		break;
	case DIRECTIONS::UP:
		// m_sprite.move(0.0f, -m_Speed);
		accel_y=-m_Speed/50.0f;
		break;
	case DIRECTIONS::DOWN:
		// m_sprite.move(0.0f, m_Speed);
		accel_y=+m_Speed/50.0f;
		break;
	default:
		break;
	}

}

void Player::physics() {
	// add friction proportional to speed absolute vector ^2
	float fric = m_Speed*std::pow(( std::pow(speed_x, 2.00f) + std::pow(speed_y, 2.00f) ), 0.5f) / 500.0f;
	if (speed_x > 0) {speed_x-=fric;}
	else if (speed_x < 0) {speed_x+=fric;}
	if (speed_y > 0) {speed_y-=fric*1.25f;}
	else if (speed_y < 0) {speed_y+=fric*1.25f;}
	// propagate accel to vel
	speed_x+=accel_x;
	speed_y+=accel_y*1.25f;
	//reset accel
	accel_x = 0;
	accel_y = 0;
	//move vel
	m_sprite.move(speed_x, speed_y);
}

void Player::shoot()
{

}

void Player::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(0.5f, 0.5f);
}

bool Player::collidesWith(const Enemy& enemy)
{
	return m_sprite.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds());
}

bool Player::collidesWith(const EnemyBullet& enemybullet)
{
	return m_sprite.getGlobalBounds().intersects(enemybullet.getSprite().getGlobalBounds());
}

bool Player::collidesWith(const Item_& iem)
{
	//placeholder
	return true;
}

