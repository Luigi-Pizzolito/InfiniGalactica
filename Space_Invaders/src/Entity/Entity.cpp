#include "Entity.h"
#include "Projectiles/Projectile.h"


Entity::Entity(int health,float speed):m_MaxHP(health),m_HP(health),
	m_Speed(speed)
{
	// m_sprite.setTexture(*m_texture);
}

Entity::~Entity()
{

}

void Entity::move(DIRECTIONS dir)
{
	//Example

	//switch (dir)
	//{
	//case DIRECTIONS::LEFT:
	//	m_sprite.move(-m_Speed, 0.0f);
	//	break;
	//case DIRECTIONS::RIGHT:
	//	m_sprite.move(m_Speed, 0.0f);
	//	break;
	//case DIRECTIONS::UP:
	//	m_sprite.move(0.0f, m_Speed);
	//	break;
	//case DIRECTIONS::DOWN:
	//	m_sprite.move(0.0f, -m_Speed);
	//	break;
	//default:
	//	break;
	//}


}

void Entity::setTexture(const sf::Texture& texture)
{
	//This function must bind the Entity with an external texture
}

sf::Vector2f Entity::getSize()
{
	return sf::Vector2f(m_sprite.getTextureRect().width * m_sprite.getScale().x, m_sprite.getTextureRect().height * m_sprite.getScale().y);
}

sf::Vector2f Entity::getTopLeftPos()
{
	return sf::Vector2f(m_sprite.getPosition());
}

