#include "Entity.h"
#include "Projectiles/Projectile.h"

Entity::Entity(int health,float speed):m_MaxHP(health),m_HP(health),
	m_Speed(speed)
{
	
}
Entity::~Entity()
{
	//virtual destructor for polymorphic behavior
}
void Entity::move(DIRECTIONS dir)
{



}
void Entity::setTexture(const sf::Texture& texture)
{
	//This function must bind the Entity with an external texture
}
const sf::Vector2f Entity::getSize()const
{
	return sf::Vector2f(m_sprite.getTextureRect().width * m_sprite.getScale().x, m_sprite.getTextureRect().height * m_sprite.getScale().y);
}
const sf::Vector2f& Entity::getTopLeftPos()const 
{
	return m_sprite.getPosition();
}

