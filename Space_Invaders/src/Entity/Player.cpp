#include "Player.h"
#include "Enemy.h"
#include "Projectiles/Projectile.h"
#include "MediaManager/SFXPlayer.h"


Player::Player(int health, float speed, float fric):PhysicsEntity(health,speed,fric),player_speed(speed),player_friction(fric)
{
	player_bullet_timer.setDuration(0.5f);
	m_sprite.setScale(0.5f, 0.5f);
}

Player::~Player()
{
	SFX::play(SFXlib::EnemyDestroy);
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



void Player::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	
}
bool Player::collidesWith(Enemy* enemy)
{
	return m_sprite.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds());
}
bool Player::collidesWith(EnemyBullet* enemybullet)
{
	return m_sprite.getGlobalBounds().intersects(enemybullet->getSprite().getGlobalBounds());
}
bool Player::collidesWith(Item_* iem)
{
	//placeholder
	return true;
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
