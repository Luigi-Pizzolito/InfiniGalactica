#include "PhysicsEntity.h"
#include <cmath>

PhysicsEntity::PhysicsEntity(int health, float speed, float fric):Entity(health,speed),fric_divisor(fric),base_speed(speed) {
    
}

PhysicsEntity::~PhysicsEntity() {

}



void PhysicsEntity::updatePhysics() {
    // add friction proportional to speed absolute vector ^2 weighted by fric_divisor
	float fric = base_speed * std::sqrt( veloc.x*veloc.x + veloc.y*veloc.y ) / fric_divisor;
	if (veloc.x > 0) {veloc.x-=fric;}
	else if (veloc.x < 0) {veloc.x+=fric;}
	if (veloc.y > 0) {veloc.y-=fric*1.25f;}
	else if (veloc.y < 0) {veloc.y+=fric*1.25f;} //? compensate y vel asymetry by adding more y fric
	// propagate accel to vel
	accel.y*=1.25f; //? y vel asymetry in order to add better player manauverability in y-axis
	veloc+=accel;
	//reset accel
	accel = sf::Vector2f();
	//move vel
	m_sprite.move(veloc);
}

void PhysicsEntity::applyForce(sf::Vector2f force, float force_divisor) {
    // Add force to acceleration, force_divisor is basically mass as F=ma aka. a=F/m
	force/=force_divisor;
	accel+=force;
}