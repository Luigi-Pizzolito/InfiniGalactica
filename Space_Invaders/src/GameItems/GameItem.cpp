#include "GameItem.h"
#include "Entity/Player.h"
#include "SceneManager/Scene.h"

GameItem::GameItem(float q_effect):m_buffQuantity(q_effect)
{

}

GameItem::~GameItem()
{
}

void GameItem::setTexture(const sf::Texture& texture,const sf::Vector2f scalevec)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(scalevec);
}

void GameItem::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
	
}


void GameItem::setPosition(float x_pos)
{
	m_sprite.setPosition(x_pos, rand() % static_cast<int>(SceneManagement::Scene::s_view->getSize().y - getSize().y));

}

const sf::Vector2f GameItem::getSize() const
{
	return sf::Vector2f(m_sprite.getTextureRect().width * m_sprite.getScale().x, m_sprite.getTextureRect().height * m_sprite.getScale().y);


}

const sf::Vector2f& GameItem::getTopLeftPos() const
{
	return m_sprite.getPosition();
}

HealthPackage::HealthPackage(float q_effect):GameItem(q_effect)
{

}

HealthPackage::~HealthPackage()
{

}

void HealthPackage::applyEffect(Player* player)
{
	player->heal(m_buffQuantity);
}


FireRateBooster::FireRateBooster(float q_effect):GameItem(q_effect)
{

}

FireRateBooster::~FireRateBooster()
{
	
}

void FireRateBooster::applyEffect(Player* player)
{
	player->boostFireRate(m_buffQuantity);
}

DamageBooster::DamageBooster(float q_effect) :GameItem(q_effect)
{

}

DamageBooster::~DamageBooster()
{

}

void DamageBooster::applyEffect(Player* player)
{
	player->increaseBulletDamage(m_buffQuantity);
}
