#include "Bosses.h"
#include "Projectiles/Projectile.h"
#include "Algorithms/MathUtils.h"
Boss::Boss(int health, float speed, const sf::Vector2f& dir)
	:Enemy(health,speed,dir)
{

}


Boss::~Boss()
{
	if (points) {
		delete[] points;
		points = nullptr;
	}
}

//just as a reminder that we need to set the texture
void Boss::setTexture(const sf::Texture& texture, const sf::Vector2f& scalevec)
{
	//set the texture
	m_sprite.setTexture(texture);
	//recenter
	m_sprite.setOrigin(getSize() / 2.0f);
	//set scale
	m_sprite.setScale(scalevec);
	
}

//Commander
Commander::Commander(int health, float speed, const sf::Vector2f& dir)
	:Boss(health,speed,dir),m_max_attack_num(3),m_current_attack_left(0),m_current_state(STATES::IDLE)
{
	m_bullets_count = 7;
	points = new sf::Vector2f[m_bullets_count];
	m_state_changer.setDuration(3.0f);
}

Commander::~Commander()
{

}

EnemyBullet* Commander::spawnBullet(int bullet_index)
{
	//lower cannons
	EnemyBullet* projectile = nullptr;
	//randomize the deviation pattern

	if (bullet_index < 3) {
		projectile = new DeviatedProjectile(m_bullet_damage,m_bullet_speed,points[bullet_index],VectorMath::Vdirection::LEFT,deviation_dir[m_current_convention]*(-5.0f));
	}
	else if (bullet_index < 6) {
		projectile = new DeviatedProjectile(m_bullet_damage, m_bullet_speed, points[bullet_index], VectorMath::Vdirection::LEFT, deviation_dir[m_current_convention] *(5.0f));

	}
	else {
		projectile = new EnemyBullet(m_bullet_damage, m_bullet_speed, points[bullet_index], VectorMath::Vdirection::LEFT);

	}
	projectile->setTexture(*m_projectile_texture, m_projectile_scale);
	return projectile;
}

void Commander::updateStates()
{
	//Handle the bosses actions
	
	m_state_changer.start();
	
	switch (m_current_state)
	{
	case Commander::STATES::IDLE:
		setPoints();
		if (m_state_changer.timeOut()) {
			
			//sets the attack state
			m_current_state = STATES::ATTACK;
			//how many shots
			m_current_attack_left = (std::rand() % (m_max_attack_num))+1;
			//the convention of the deviation
			m_current_convention = std::rand() % (2);
		}
		break;
	case Commander::STATES::MOVE:
		
		move();
		setPoints();
		if (m_state_changer.timeOut()) { m_current_state = STATES::IDLE; }
		break;
	case Commander::STATES::ATTACK:
		
		//After attacking certain number of times, it moves
		m_shoot_timer.start();
		if (m_shoot_timer.timeOut()) { 
			can_shoot = true;
			m_current_attack_left--;
		
		}
		if (m_current_attack_left <= 0) { 
			m_current_state = STATES::MOVE; }
		break;
	default:
		break;
	}
}

void Commander::move()
{
	//if touches the limits of the viewport it changes direction
	//check the upper limit
	if (getCenterPos().y - getSize().y / 2.0f <= VectorMath::getViewPortTopLeftPos().y) {
		m_dir = VectorMath::Vdirection::DOWN;
	}
	//check the lower limit
	else if (getCenterPos().y + getSize().y / 2.0f >= VectorMath::getViewportLowerRightPos().y) {
		m_dir = VectorMath::Vdirection::UP;
	}
	m_sprite.move(m_dir * m_Speed);
}

bool Commander::canShoot()
{
	bool canshoot = can_shoot;
	if (can_shoot) {
		m_state_changer.restart();
		can_shoot = false;
	}
	return canshoot;
}

void Commander::setPoints()
{
	
	//lower points
	points[0] = getCenterPos() + sf::Vector2f(-getSize().x * 0.27f, getSize().y * 0.4f) / 2.0f;
	points[1] = getCenterPos() + sf::Vector2f(-getSize().x * 0.27f, getSize().y * 0.56f) / 2.0f;
	points[2] = getCenterPos() + sf::Vector2f(-getSize().x * 0.27f, getSize().y * 0.71f) / 2.0f;
	//upper points
	points[3] = getCenterPos() + sf::Vector2f(-getSize().x * 0.27f, -getSize().y * 0.4f) / 2.0f;
	points[4] = getCenterPos() + sf::Vector2f(-getSize().x * 0.27f, -getSize().y * 0.56f) / 2.0f;
	points[5] = getCenterPos() + sf::Vector2f(-getSize().x * 0.27f, -getSize().y * 0.71f) / 2.0f;
	//mid point
	points[6] = VectorMath::getAABBMidBack(getCenterPos(), getSize());
}
//Commander Attacker

CommanderAttacker::CommanderAttacker(int health, float speed, const sf::Vector2f& dir, float timer_duration)
	:Boss(health, speed, dir), m_max_attack_num(4), m_current_attack_left(0), m_current_state(STATES::MOVE)
{
	m_bullets_count = 13;
	points = new sf::Vector2f[m_bullets_count];
	m_state_changer.setDuration(timer_duration);
}

CommanderAttacker::~CommanderAttacker()
{

}

EnemyBullet* CommanderAttacker::spawnBullet(int bullet_index)
{
	EnemyBullet* bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, points[bullet_index], VectorMath::Vdirection::LEFT);
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}

void CommanderAttacker::updateStates()
{

	//Handle the bosses actions
	
	if(m_HP>0){
		m_state_changer.start();
		switch (m_current_state)
		{
		case CommanderAttacker::STATES::IDLE:
			
			if (m_state_changer.timeOut()) {

				//sets the attack state
				m_current_state = STATES::ATTACK;
				//how many shots
				m_current_attack_left = (std::rand() % (m_max_attack_num+1)) + 1;
				
			}
			break;
		case CommanderAttacker::STATES::MOVE:
			if (!ready) {
				if ((getCenterPos().x + getSize().x / 2.0f) <= VectorMath::getViewportLowerRightPos().x) {
	
					ready = true;
					m_state_changer.restart();
					m_current_state = STATES::ATTACK;
					m_current_attack_left = (std::rand() % (m_max_attack_num + 1)) + 1;
				}
				else {
					m_sprite.move(VectorMath::Vdirection::LEFT * m_Speed);
				}
			}
			else {
				//It is ready
				move();
				if (m_state_changer.timeOut()) { m_current_state = STATES::IDLE; }
			}

			break;
		case CommanderAttacker::STATES::ATTACK:

			//After attacking certain number of times, it moves
			m_shoot_timer.start();
			if (m_shoot_timer.timeOut()) {
				can_shoot = true;
				m_current_attack_left--;

			}
			if (m_current_attack_left <= 0) {
				m_current_state = STATES::MOVE;
			}
			break;
		default:
			break;
		}
		setPoints();
	}
	else {
		if (m_HP < 0) {
			m_HP = 0;
		}
		m_sprite.move(VectorMath::Vdirection::RIGHT * m_Speed);
		if (getCenterPos().x-getSize().x/2.0f>=VectorMath::getViewportLowerRightPos().x) {
			in_position = true;
		}
	}
}

void CommanderAttacker::move()
{
	//if touches the limits of the viewport it changes direction
//check the upper limit
	if (getCenterPos().y - getSize().y / 2.0f <= VectorMath::getViewPortTopLeftPos().y) {
		m_dir = VectorMath::Vdirection::DOWN;
	}
	//check the lower limit
	else if (getCenterPos().y + getSize().y / 2.0f >= VectorMath::getViewportLowerRightPos().y) {
		m_dir = VectorMath::Vdirection::UP;
	}
	m_sprite.move(m_dir * m_Speed);
}

bool CommanderAttacker::canShoot()
{
	bool canshoot = can_shoot;
	if (can_shoot) {
		m_state_changer.restart();
		can_shoot = false;
	}
	return canshoot;
}

void CommanderAttacker::setPoints()
{
	//lower points
	points[0] = getCenterPos() + sf::Vector2f(-getSize().x*0.83f, getSize().y*0.52f)/2.0f;
	points[1] = getCenterPos() + sf::Vector2f(-getSize().x, getSize().y*0.60f) / 2.0f;
	points[2] = getCenterPos() + sf::Vector2f(-getSize().x*0.83f, getSize().y*0.7f) / 2.0f;
	points[3] = getCenterPos() + sf::Vector2f(-getSize().x*0.6f, getSize().y*0.78f) / 2.0f;
	points[4] = getCenterPos() + sf::Vector2f(-getSize().x*0.68f, getSize().y*0.84f) / 2.0f;
	points[5] = getCenterPos() + sf::Vector2f(-getSize().x*0.6f, getSize().y*0.91f) / 2.0f;
	//upper points 
	points[6] = getCenterPos() + sf::Vector2f(-getSize().x * 0.83f, -getSize().y * 0.52f) / 2.0f;
	points[7] = getCenterPos() + sf::Vector2f(-getSize().x, -getSize().y * 0.60f) / 2.0f;
	points[8] = getCenterPos() + sf::Vector2f(-getSize().x * 0.83f, -getSize().y * 0.7f) / 2.0f;
	points[9] = getCenterPos() + sf::Vector2f(-getSize().x * 0.6f, -getSize().y * 0.78f) / 2.0f;
	points[10] = getCenterPos() + sf::Vector2f(-getSize().x * 0.68f, -getSize().y * 0.84f) / 2.0f;
	points[11] = getCenterPos() + sf::Vector2f(-getSize().x * 0.6f, -getSize().y * 0.91f) / 2.0f;
	//mid point
	points[12]= VectorMath::getAABBMidBack(getCenterPos(), getSize());
}

CommanderStarminator::CommanderStarminator(int health, float speed, float rotation_speed, const sf::Vector2f& dir)
	:Boss(health,speed,dir), m_max_attack_num(3), m_current_attack_left(0), 
	m_current_state(STATES::IDLE),m_rotation_angle(rotation_speed),m_iteration(2)
{
	m_bullets_count = 5;
	points = new sf::Vector2f[m_bullets_count];
	m_state_changer.setDuration(3.0f);

}

CommanderStarminator::~CommanderStarminator()
{

}

EnemyBullet* CommanderStarminator::spawnBullet(int bullet_index)
{
	EnemyBullet* bullet = nullptr;
	if (bullet_index < 4) {
		 bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, getCenterPos() + points[bullet_index], VectorMath::getUnitaryVector(points[bullet_index]));

	}
	else {
		bullet = new EnemyBullet(m_bullet_damage, m_bullet_speed, getCenterPos(), m_target_pos_dir);

	}
	bullet->setTexture(*m_projectile_texture, m_projectile_scale);
	return bullet;
}

void CommanderStarminator::updateStates()
{
	//Handle the bosses actions

	m_state_changer.start();

	switch (m_current_state)
	{
	case CommanderStarminator::STATES::IDLE:
		
		if (m_state_changer.timeOut()) {

			//sets the attack state
			m_current_state = STATES::ATTACK;
			//how many shots
			m_current_attack_left = (std::rand() % (m_max_attack_num)) + 1;

		}
		break;
	case CommanderStarminator::STATES::MOVE:
		move();
		if (m_state_changer.timeOut()) { m_current_state = STATES::IDLE; }
		break;
	case CommanderStarminator::STATES::ATTACK:

		//After attacking certain number of times, it moves
		m_shoot_timer.start();
		if (m_shoot_timer.timeOut()) {
			can_shoot = true;
			m_current_attack_left--;

		}
		if (m_current_attack_left <= 0) {
			m_current_state = STATES::MOVE;
		}
		break;
	default:
		break;
	}
	m_sprite.rotate(m_rotation_angle);
	setPoints();
}

void CommanderStarminator::move()
{
	//check the upper limit
	if (getCenterPos().y - getSize().y / 2.0f <= VectorMath::getViewPortTopLeftPos().y) {
		m_dir = VectorMath::Vdirection::DOWN;
	}
	//check the lower limit
	else if (getCenterPos().y + getSize().y / 2.0f >= VectorMath::getViewportLowerRightPos().y) {
		m_dir = VectorMath::Vdirection::UP;
	}
	m_sprite.move(m_dir * m_Speed);
}

bool CommanderStarminator::canShoot()
{
	bool canshoot = can_shoot;
	if (can_shoot) {
		m_state_changer.restart();
		can_shoot = false;
	}
	return canshoot;
}

void CommanderStarminator::lookAt(const sf::Vector2f& target_pos)
{
	m_target_pos_dir = VectorMath::getUnitaryVector(getCenterPos(), target_pos);
}

void CommanderStarminator::setPoints()
{
	sf::Transform trans_format;
	trans_format.rotate(m_rotation_angle * (m_iteration));
	//set the points 
	//left-right
	points[0] = sf::Vector2f(-getSize().x / 2.0f, 0.0f);
	points[1] = sf::Vector2f(+getSize().x / 2.0f, 0.0f);
	//up-down
	points[2] = sf::Vector2f(0.0f, -getSize().y / 2.0f);
	points[3] = sf::Vector2f(0.0f, getSize().y / 2.0f);
	if (m_rotation_angle > 0) {
		//create a transformation matrix

		for (uint8_t i = 0; i < m_bullets_count; i++) {
			points[i] = trans_format.transformPoint(points[i]);
		}
		m_iteration++;
	}
	points[4] = m_target_pos_dir;
}
