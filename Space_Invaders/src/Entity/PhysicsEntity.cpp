#include "PhysicsEntity.h"
#include <cmath>

PhysicsEntity::PhysicsEntity(int health, float speed, float fric):Entity(health,speed),fric_divisor(fric),base_speed(speed) {
    
}

PhysicsEntity::~PhysicsEntity() {

}



void PhysicsEntity::updatePhysics() {
	// propagate accel to vel, and reset accell
	veloc+=accel;
	accel = sf::Vector2f();

    // add friction proportional to speed vector  weighted by fric_divisor
	sf::Vector2f friction = sf::Vector2f(veloc.x*veloc.x, veloc.y*veloc.y)/fric_divisor;
	if (veloc.x > 0) {veloc.x-=friction.x;}
	else if (veloc.x < 0) {veloc.x+=friction.x;}
	if (veloc.y > 0) {veloc.y-=friction.y;}
	else if (veloc.y < 0) {veloc.y+=friction.y;}

	// add repulsion if near screen edges
	// sf::Vector2f
	
	//move vel
	m_sprite.move(veloc);
}

void PhysicsEntity::applyForce(sf::Vector2f force) {
    // Add force to acceleration, force_divisor is basically mass as F=ma aka. a=F/m
	// force/=force_divisor;
	accel+=force;
}