#pragma once
#include <vector>
#include "Algorithms/Utilities.h"
#include "Algorithms/MathUtils.h"
#include "SceneManager/Scene.h"
#include "GameItems/GameItem.h"
//Forward declaration
class Enemy;
class GameItem;
namespace MemoryManagement {
	class BaseEnemySpawner {
	protected:
		std::vector<Enemy*>& buffer_alias;
		sf::Vector2f& m_world_pos;
		sf::Vector2f& m_total_length;
	public: 
		BaseEnemySpawner(std::vector<Enemy*>& enemy_buffer,sf::Vector2f& world_pos,sf::Vector2f& total_length) :
			buffer_alias(enemy_buffer),m_world_pos(world_pos),m_total_length(total_length)
		{
	
		}
		virtual ~BaseEnemySpawner(){}
		virtual void update(){}
		virtual void spawn(){}

	};
	template<typename T>
	class EnemySpawner:public BaseEnemySpawner {
		
	public:
		//own members
		//Remember to set the duration of the timer
		Control::GameTimer timer;
		float timer_duration = 1.0f;
		//Type-1 enemy
		sf::Texture t1_enemy_texture;
		sf::Vector2f t1_enemy_scale;
		uint8_t t1_speed = 10;
		uint16_t t1_health = 20;
		sf::Texture t1_bullet_texture;
		sf::Vector2f t1_bullet_scale;
		uint8_t t1_bullet_damage = 10;
		uint8_t t1_bullet_speed = 15;
		//Type-2 enemy
		sf::Texture t2_enemy_texture;
		sf::Vector2f t2_enemy_scale;
		uint8_t t2_speed = 5;
		uint16_t t2_health = 30;
		sf::Texture t2_bullet_texture;
		sf::Vector2f t2_bullet_scale;
		uint8_t t2_bullet_damage = 20;
		uint8_t t2_bullet_speed = 15;
		EnemySpawner(std::vector<Enemy*>& enemy_buffer, sf::Vector2f& world_pos, sf::Vector2f& total_length) :BaseEnemySpawner(enemy_buffer,world_pos,total_length) {
			timer.setDuration(timer_duration);
			//default values
			//Type-1
			std::string path_texture_1("res/Sprites/enemies/recon.png");
			t1_enemy_scale = { 0.5f,0.5f };
			std::string path_projectile_texture1("res/Sprites/projectiles/laser_red.png");
			t1_bullet_scale = { 0.4f,0.3f };
			//Type
			std::string path_projectile_texture2("res/Sprites/projectiles/laser_blue.png");
			t2_enemy_scale = { 0.5f,0.5f };
			std::string path_texture_2("res/Sprites/enemies/recon_v2.png");
			t2_bullet_scale = { 0.4f,0.3f };
			///json data values
	

			//enemy textures
			t1_enemy_texture.loadFromFile(path_texture_1);
			t2_enemy_texture.loadFromFile(path_texture_2);
			//projectile textures
			t1_bullet_texture.loadFromFile(path_projectile_texture1);
			t2_bullet_texture.loadFromFile(path_projectile_texture2);

		}

		void update()override {
			timer.start();
			if (timer.timeOut()) {
				spawn();
			}
				
		}
		void spawn()override {
			float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;

			if (percent_of_progress<20.0f) {

				buffer_alias.emplace_back(new T(t1_health, t1_speed, VectorMath::Vdirection::LEFT));
				//set the texture
				buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
				//set the projectile texture
				buffer_alias.back()->setProjectileTexture(t1_bullet_texture, t1_bullet_scale);
				//call set bullet parameters
				buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);
			}
			else if (percent_of_progress < 40.0f) {
				buffer_alias.emplace_back(new T(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(t2_enemy_texture, t2_enemy_scale);
				buffer_alias.back()->setProjectileTexture(t2_bullet_texture, t2_bullet_scale);
				buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

			}
			else {
				int range = 1 - 0 + 1;
				int type = rand() % range + 0;

				if (type == 0) {
					//create the enemy
					buffer_alias.emplace_back(new T(t1_health, t1_speed, VectorMath::Vdirection::LEFT));
					//set the texture
					buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
					//set the projectile texture
					buffer_alias.back()->setProjectileTexture(t1_bullet_texture, t1_bullet_scale);
					//call set bullet parameters
					buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);
				}
				else {

					buffer_alias.emplace_back(new T(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
					buffer_alias.back()->setTexture(t2_enemy_texture, t2_enemy_scale);
					buffer_alias.back()->setProjectileTexture(t2_bullet_texture, t2_bullet_scale);
					buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

				}
			}

		
			buffer_alias.back()->setPosition(sf::Vector2f(VectorMath::getViewportLowerRightPos().x,SceneManagement::Scene::s_view->getSize().y));
			// std::cout << m_world_pos << ", " << buffer_alias.back()->getCenterPos() << "\n";
			// std::cin.get();
		}
	};
	//change this later
	class BaseItemSpawner{
	protected:
		std::vector<GameItem*>& buffer_alias;
		Control::GameTimer timer;
		sf::Texture health_package_texture;
		sf::Texture fire_rate_booster_texture;
		sf::Texture damage_booster_texture;
		//only one scale because our current textures have the same size
		//if we change to different textures, then set different scales
		sf::Vector2f general_scale = { 1.0f,1.0f };
	public:
		BaseItemSpawner(std::vector<GameItem*>& item_buffer) :buffer_alias(item_buffer) {
			timer.setDuration(10.0f);
			std::string health_package_path("res/Sprites/items/health_package.png");
			std::string fire_rate_booster_path("res/Sprites/items/fire_rate_booster.png");
			std::string damage_booster_path("res/Sprites/items/damage_booster.png");
			//json 

			health_package_texture.loadFromFile(health_package_path);
			fire_rate_booster_texture.loadFromFile(fire_rate_booster_path);
			damage_booster_texture.loadFromFile(damage_booster_path);
		}
		//make it virtual later
		~BaseItemSpawner() {}
		void update() {
			timer.start();
			if (timer.timeOut()) {
				spawn();
			}
		}
		void spawn() {
			//change laters
			static int x = 0;
			if (x == 0) {
				buffer_alias.emplace_back(new HealthPackage(25.0f));
				buffer_alias.back()->setTexture(health_package_texture,general_scale);
			}
			else if (x == 1) {
				buffer_alias.emplace_back(new FireRateBooster(20.0f));
				buffer_alias.back()->setTexture(fire_rate_booster_texture,general_scale);
			}
			else {
				buffer_alias.emplace_back(new DamageBooster(10.0f));
				buffer_alias.back()->setTexture(damage_booster_texture,general_scale);
				
			}
			x++;
			if (x > 2) {
				x = 0;
			}
			buffer_alias.back()->setPosition(sf::Vector2f(VectorMath::getViewportLowerRightPos().x, SceneManagement::Scene::s_view->getSize().y));
			
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

