#include "Player.h"
#include "Enemy.h"
#include "Projectiles/Projectile.h"

Player::Player(int health, float speed, float fric):PhysicsEntity(health,speed, fric)
{

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
		applyForce(sf::Vector2f(-m_Speed, 0.0f), 50.0f);		// movement is done by applyForce with a sf::Vector2f and a force divisor float
		break;
	case DIRECTIONS::RIGHT:
		applyForce(sf::Vector2f(m_Speed, 0.0f), 50.0f);
		break;
	case DIRECTIONS::UP:
		applyForce(sf::Vector2f(0.0f, -m_Speed), 50.0f);
		break;
	case DIRECTIONS::DOWN:
		applyForce(sf::Vector2f(0.0f, m_Speed), 50.0f);
		break;
	default:
		break;
	}

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

