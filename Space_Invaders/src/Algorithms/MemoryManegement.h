#pragma once
#include <vector>
#include "Algorithms/Utilities.h"
#include "SceneManager/Scene.h"
//Forward declaration
class Enemy;

namespace MemoryManagement {
	class BaseEnemySpawner {
	protected:
		std::vector<Enemy*>& buffer_alias;
	public: 
		BaseEnemySpawner(std::vector<Enemy*>& enemy_buffer) :buffer_alias(enemy_buffer) {
	
		}
		virtual ~BaseEnemySpawner(){}
		virtual void update(){}
		virtual void spawn(){}

	};
	template<typename T>
	class EnemySpawner:public BaseEnemySpawner {
		//target buffer
	
	public:
		//prototype of the enemy
		//Note Load the Texture!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		sf::Texture enemy_texture;
		//Type-1 small
		uint8_t t1_speed = 5;
		uint16_t t1_health = 45;
		//Type-2 big
		uint8_t t2_speed = 10;
		uint16_t t2_health = 25;
		float timer_duration = 1.0f;
		//Control- Remember to set the duration of the timer
		//Todo
		//Add a bullet type, so it can know what kind of bullet it needs to spawn
		//or specify the bullet type withing a function for that enemy class
		Control::GameTimer timer;
		EnemySpawner(std::vector<Enemy*>& enemy_buffer):BaseEnemySpawner(enemy_buffer){
			timer.setDuration(timer_duration);
			enemy_texture.loadFromFile("res/Sprites/enemy1.png");
		}

		void update()override {
			timer.start();
			if (timer.timeOut()) {
				spawn();
			}
				
		}
		void spawn()override {
			//health,speed,direction
			int range = 1 - 0 + 1;
			int type = rand() % range + 0;
			
			//Only two types
			if (type == 0) {
				buffer_alias.emplace_back(new T(t1_health,t1_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(enemy_texture);
				
			}
			else {
	
				buffer_alias.emplace_back(new T(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(enemy_texture);
				buffer_alias.back()->setSprite().setScale(0.3, 0.3);

			}
		
			buffer_alias.back()->setPosition(sf::Vector2f(VectorMath::getViewportLowerRightPos().x,SceneManagement::Scene::s_view->getSize().y));
		}
	};
	class BasicCollector {
	public:
		BasicCollector(){}
		virtual ~BasicCollector(){}
		virtual void update(){}
		

	};

	template<typename T>
	class Collector:public BasicCollector {
	protected:
		std::vector<T*>& buffer_alias;
	public:
		Collector(std::vector<T*>& buffer):buffer_alias(buffer) {

		}
		void update() override {
			
			buffer_alias.erase(std::remove_if(buffer_alias.begin(), buffer_alias.end(),
				[&](T* obj) {
					//first delete the heap mem
					bool out_of_range = leftViewport(obj);
					if (out_of_range) {
						delete obj;}
					return out_of_range; }),buffer_alias.end());

	
		}
		bool leftViewport(const T* obj) {
			sf::Vector2f top_left_pos = VectorMath::getViewPortTopLeftPos();
			sf::Vector2f lower_right_pos = VectorMath::getViewportLowerRightPos();
			//x axis
			bool far_from_right_side = obj->getTopLeftPos().x > lower_right_pos.x + obj->getSize().x;
			bool far_from_left_side = obj->getTopLeftPos().x < top_left_pos.x - obj->getSize().x;
			//y axis
			bool far_from_top = obj->getTopLeftPos().y < top_left_pos.y - obj->getSize().y;
			bool far_from_bottom = obj->getTopLeftPos().y > lower_right_pos.y + obj->getSize().y;

			return (far_from_right_side || far_from_left_side || far_from_top || far_from_bottom);
		}
	};

}

