#pragma once
#include "Entity.h"

//Class Implemented by Luigi 03.03 22:26
class PhysicsEntity:public Entity {
    protected:
        sf::Vector2f accel;
        sf::Vector2f veloc;
        float base_speed;
        float fric_divisor;

    public:
        PhysicsEntity(int health, float speed, float fric);
        ~PhysicsEntity();

        // add this to the Entity class
        void updatePhysics();
        void applyForce(sf::Vector2f force);
        sf::Vector2f* getAccel() {return &accel;};
};