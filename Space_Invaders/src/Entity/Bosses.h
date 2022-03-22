#pragma once
#include "Enemy.h"
#include "Algorithms/Utilities.h"
class Boss :public Enemy {
protected:
	sf::Vector2f* points;
public:
	Boss(int health, float speed, const sf::Vector2f& dir);
	virtual~Boss();
	virtual EnemyBullet* spawnBullet(int bullet_index)override { return nullptr; }
	virtual void updateStates(){}
	virtual void move()override {}
	void setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)override;

protected:
	virtual void setPoints(){}
};

class Commander :public Boss {
	enum class STATES:uint8_t {
		IDLE=0, MOVE,ATTACK
	};
	STATES m_current_state;
	Control::GameTimer m_state_changer;
	int m_max_attack_num;
	int m_current_attack_left;
	const int deviation_dir[2] = { -1,1 };
	int m_current_convention;
	bool can_shoot = false;
	
public:
	
	Commander(int health, float speed, const sf::Vector2f& dir);
	~Commander();
	EnemyBullet* spawnBullet(int bullet_index)override;
	void updateStates()override;
	void move()override;
	bool canShoot()override;
protected:
	void setPoints()override;
};



class CommanderStarnator :public Boss {

};

class CommenderAttacker :public Boss {

};