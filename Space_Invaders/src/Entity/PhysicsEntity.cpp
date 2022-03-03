#include "PhysicsEntity.h"
#include <cmath>

PhysicsEntity::PhysicsEntity(int health, float speed, float fric):Entity(health,speed),fric_divisor(fric),base_speed(speed) {
    // accel = sf::Vector2f();
    // veloc = sf::Vector2f(); // looks like we do not need to initialise to (0.0f,0.0f) again here
}

PhysicsEntity::~PhysicsEntity() {

}



void PhysicsEntity::updatePhysics() {
    // add friction proportional to speed absolute vector ^2 weighted by fric_divisor
	float fric = base_speed*std::pow(( std::pow(veloc.x, 2.0f) + std::pow(veloc.y, 2.0f) ), 0.5f) / fric_divisor;
	if (veloc.x > 0) {veloc.x-=fric;}
	else if (veloc.x < 0) {veloc.x+=fric;}
	if (veloc.y > 0) {veloc.y-=fric*1.25f;}
	else if (veloc.y < 0) {veloc.y+=fric*1.25f;}
	// propagate accel to vel
	veloc.x+=accel.x;
	veloc.y+=accel.y*1.25f; //? y vel asymetry in order to add better player manauverability in y-axis
	//reset accel
	accel.x = 0;
	accel.y = 0;
	//move vel
	m_sprite.move(veloc.x, veloc.y);
}

void PhysicsEntity::applyForce(sf::Vector2f force, float force_divisor) {
    // Add force to acceleration, force_divisor is basically mass as F=ma aka. a=F/m
    accel.x+=force.x/force_divisor;
    accel.y+=force.y/force_divisor;
}