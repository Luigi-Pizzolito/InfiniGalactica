#include "Player.h"
#include "Enemy.h"
#include "Projectiles/Projectile.h"


//Implemented by Daniel 03.01 11:57 AM
Player::Player(int health, float speed, float fric):PhysicsEntity(health,speed,fric),player_speed(speed),player_friction(fric)
{

}

Player::~Player()
{

}
//Implemented by Daniel 03.01 11:59 AM
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
		applyForce(sf::Vector2f(m_Speed, 0.0f));
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



//Implemented by Daniel 03.01 12:00 PM
void Player::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(0.5f, 0.5f);
}
//Implemented by Daniel 03.01 12:13 PM
bool Player::collidesWith(Enemy* enemy)
{
	return m_sprite.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds());
}
//Implemented by Daniel 03.01 12:16 PM
bool Player::collidesWith(EnemyBullet* enemybullet)
{
	return m_sprite.getGlobalBounds().intersects(enemybullet->getSprite().getGlobalBounds());
}
//Implemented by Daniel 03.01 12:18 PM
bool Player::collidesWith(Item_* iem)
{
	//placeholder
	return true;
}
//Implemented by Daniel 03.05 3:01 PM
void Player::hurt(EnemyBullet* bullet)
{
	m_HP -= bullet->getDamage();
}
//Implemented by Daniel 03.05 3:12 PM
int Player::getHP()
{
	return m_HP;
}
