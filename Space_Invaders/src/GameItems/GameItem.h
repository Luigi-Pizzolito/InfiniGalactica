#pragma once
#include <SFML/Graphics.hpp>
class Player;
class GameItem {
protected:
	sf::Sprite m_sprite;
	float m_buffQuantity;

public:
	GameItem(float q_effect);
	virtual ~GameItem();
	virtual void applyEffect(Player* player){}
	void setTexture(const sf::Texture& texture, const sf::Vector2f scalevec);
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f getSize()const;
	const sf::Vector2f& getTopLeftPos()const;
	const sf::Sprite& getSprite()const { return m_sprite; }
};
class HealthPackage :public GameItem {
public:
	HealthPackage(float q_effect);
	~HealthPackage();
	void applyEffect(Player* player)override;

};
class FireRateBooster :public GameItem {
public:
	FireRateBooster(float q_effect);
	~FireRateBooster();
	void applyEffect(Player* player)override;
};
class DamageBooster :public GameItem {
public:
	DamageBooster(float q_effect);
	~DamageBooster();
	void applyEffect(Player* player)override;
};