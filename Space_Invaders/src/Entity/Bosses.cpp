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
