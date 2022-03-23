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



class CommanderStarminator :public Boss {
	enum class STATES :uint8_t {
		IDLE = 0, MOVE, ATTACK
	};
protected:
	Control::GameTimer bullet_timer;
	STATES m_current_state;
	Control::GameTimer m_state_changer;
	int m_max_attack_num;
	int m_current_attack_left;
	bool can_shoot = false;
	float m_rotation_angle;
	int m_iteration;
	sf::Vector2f m_target_pos_dir;
public:
	CommanderStarminator(int health, float speed, float rotation_speed, const sf::Vector2f& dir);
	~CommanderStarminator();
	EnemyBullet* spawnBullet(int bullet_index)override;
	void updateStates()override;
	void move()override;
	bool canShoot()override;
	void lookAt(const sf::Vector2f& target_pos)override;
protected:
	void setPoints()override;

};

class CommanderAttacker :public Boss {
	enum class STATES :uint8_t {
		IDLE = 0, MOVE, ATTACK
	};
	STATES m_current_state;
	Control::GameTimer m_state_changer;
	int m_max_attack_num;
	int m_current_attack_left;
	bool can_shoot = false;
	bool in_position = false;
	bool ready = false;


public:

	CommanderAttacker(int health, float speed, const sf::Vector2f& dir,float timer_duration);
	~CommanderAttacker();
	EnemyBullet* spawnBullet(int bullet_index)override;
	void updateStates()override;
	void move()override;
	bool canShoot()override;
	bool isInPosition() { return in_position; }
protected:
	void setPoints()override;
};
