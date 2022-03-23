#include "Player.h"
#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include "MediaManager/SFXPlayer.h"
#include "GameItems/GameItem.h"
#include <cmath>

Player::Player(int health, float speed, float fric):PhysicsEntity(health,speed,fric),player_speed(speed),player_friction(fric)
{
	m_bullet_damage = 15;
	m_bullet_speed = 15;

	b_m_bullet_damage = m_bullet_damage;
	b_m_bullet_speed = m_bullet_speed;
	b_m_HP = m_HP;
	b_m_MaxHP = m_MaxHP;

	player_bullet_timer.setDuration(0.5f);

}

Player::~Player()
{
	SFX::play(SFXlib::EnemyDestroy);
}

void Player::setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)
{
	if (!m_centered) {
		//set the texture
		m_sprite.setTexture(texture);
		//recenter
		m_sprite.setOrigin(getSize() / 2.0f);
		//set scale
		m_sprite.setScale(scalevec);
		m_centered = true;
	}
	m_sprite.setTexture(texture);
}

void Player::setTexture(const sf::Texture& texture)
{
	if (!m_centered) {
		//set the texture
		m_sprite.setTexture(texture);
		//recenter
		m_sprite.setOrigin(getSize() / 2.0f);
	}
	m_sprite.setTexture(texture);
}

void Player::move(DIRECTIONS dir)
{
	//A player and Enemy version of the function was created just in case we want to add
	//items with effects that will change the speed of the player
	switch (dir)
	{
	case DIRECTIONS::LEFT:
		applyForce(sf::Vector2f(-m_Speed, 0.0f));		// movement is done by applyForce with a sf::Vector2f and a force divisor float
		break;
	case DIRECTIONS::RIGHT:
		applyForce(sf::Vector2f(m_Speed*1.2f, 0.0f));  // fix to compensate for reference-fram subtraction of camera base speed in this direction
		break;
	case DIRECTIONS::UP:
		applyForce(sf::Vector2f(0.0f, -m_Speed));
		break;
	case DIRECTIONS::DOWN:
		applyForce(sf::Vector2f(0.0f, m_Speed));
		break;
	default:
		break;
	}

}

void Player::applyExtForce(sf::Vector2f force) {
	
	applyForce(force);
}


bool Player::collidesWith(Enemy* enemy)
{

	return m_sprite.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds());
}
bool Player::collidesWith(EnemyBullet* enemybullet)
{
	return m_sprite.getGlobalBounds().intersects(enemybullet->getSprite().getGlobalBounds());
}


bool Player::collidesWith(GameItem* item_)
{

	return m_sprite.getGlobalBounds().intersects(item_->getSprite().getGlobalBounds());
}
void Player::hurt(EnemyBullet* bullet)
{
	m_HP -= bullet->getDamage();
	SFX::play(SFXlib::BulletHit);
}

bool Player::canShoot()
{
	
	player_bullet_timer.start();
	return player_bullet_timer.timeOut();
}

void Player::upgrade(int upgrade_lvl)
{
	m_MaxHP 		= b_m_MaxHP 		*std::pow(1.25f, upgrade_lvl);
	
	m_bullet_speed 	= b_m_bullet_speed	*std::pow(1.1f , upgrade_lvl);
	m_bullet_damage = b_m_bullet_damage	*std::pow(1.1f , upgrade_lvl);
}

void Player::upgradeHP(int upgrade_lvl) {
	m_HP 			= getHP()			*std::pow(1.25f, upgrade_lvl);
}

void Player::heal(float quantity)
{
	m_HP += quantity;
	if (m_HP > m_MaxHP) {
		m_HP = m_MaxHP;}
}

void Player::boostFireRate(float percent_increment)
{
	player_bullet_timer.setDuration(player_bullet_timer.getDuration() * (1-percent_increment/100.0f));
}

void Player::increaseBulletDamage(float increment)
{
	m_bullet_damage += increment;
}

void Player::increaseBulletSpeed(float increment)
{
	m_bullet_speed += increment;
}
