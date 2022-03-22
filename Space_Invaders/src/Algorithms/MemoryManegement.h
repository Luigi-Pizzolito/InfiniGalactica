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
		//own members
		//Remember to set the duration of the timer
		Control::GameTimer timer;
		float timer_duration = 3.0f;
		//textures
		std::vector<sf::Texture> enemy_textures;
		std::vector<sf::Texture> bullet_textures;
		//Type-1 enemy
		sf::Vector2f t1_enemy_scale;
		uint8_t t1_speed = 10;
		uint16_t t1_health = 20;
		sf::Vector2f t1_bullet_scale;
		uint8_t t1_bullet_damage = 10;
		uint8_t t1_bullet_speed = 15;
		//Type-2 enemy
		sf::Vector2f t2_enemy_scale;
		uint8_t t2_speed = 5;
		uint16_t t2_health = 30;
		sf::Vector2f t2_bullet_scale;
		uint8_t t2_bullet_damage = 20;
		uint8_t t2_bullet_speed = 15;
	public: 
		BaseEnemySpawner(std::vector<Enemy*>& enemy_buffer,sf::Vector2f& world_pos,sf::Vector2f& total_length) :
			buffer_alias(enemy_buffer),m_world_pos(world_pos),m_total_length(total_length)
		{
			//initialize here


		}
		virtual ~BaseEnemySpawner(){}
		void update() {
			timer.start();
			if (timer.timeOut()) {
				spawn();
			}

		}
		virtual void spawn(){}

	};
	//Later use this as the default spawner
	template<typename T>
	class EnemySpawner:public BaseEnemySpawner {
		
	public:

		EnemySpawner(std::vector<Enemy*>& enemy_buffer, sf::Vector2f& world_pos, sf::Vector2f& total_length) :BaseEnemySpawner(enemy_buffer,world_pos,total_length) {
			//timer.setDuration(timer_duration);
			timer.setDuration(1.0f);
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
	

			//Load the textures
			//enemy textures
			sf::Texture t1_enemy_texture;
			t1_enemy_texture.loadFromFile(path_texture_1);
			sf::Texture t2_enemy_texture;
			t2_enemy_texture.loadFromFile(path_texture_2);
			//projectile textures
			sf::Texture t1_bullet_texture;
			t1_bullet_texture.loadFromFile(path_projectile_texture1);
			sf::Texture t2_bullet_texture;
			t2_bullet_texture.loadFromFile(path_projectile_texture2);

			//you can probably iterate over the json keys
			// create temp textures, and then emplace them back
			// to the respective vector
			//Emplace back
			enemy_textures.emplace_back(t1_enemy_texture);
			enemy_textures.emplace_back(t2_enemy_texture);
			bullet_textures.emplace_back(t1_bullet_texture);
			bullet_textures.emplace_back(t2_bullet_texture);
	
		}


		void spawn()override {
			float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;

			if (percent_of_progress<20.0f) {

				buffer_alias.emplace_back(new T(t1_health, t1_speed, VectorMath::Vdirection::LEFT));
				//set the texture
				buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);
				//set the projectile texture
				buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
				//call set bullet parameters
				buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);
			}
			else if (percent_of_progress < 40.0f) {
				buffer_alias.emplace_back(new T(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
				buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
				buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

			}
			else {
				int range = 1 - 0 + 1;
				int type = rand() % range + 0;

				if (type == 0) {
					buffer_alias.emplace_back(new T(t1_health, t1_speed, VectorMath::Vdirection::LEFT));
					//set the texture
					buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);
					//set the projectile texture
					buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
					//call set bullet parameters
					buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);
				}
				else {

					buffer_alias.emplace_back(new T(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
					buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
					buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
					buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

				}
			}

		
			buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
		}
	};
	//delete!!!!!!!!!!!!!!!!!!!!!
	template<> class EnemySpawner<Furtive> :public BaseEnemySpawner {
	public:
	
		EnemySpawner(std::vector<Enemy*>& enemy_buffer, sf::Vector2f& world_pos, sf::Vector2f& total_length) :BaseEnemySpawner(enemy_buffer, world_pos, total_length) {
			//set the textures
			timer.setDuration(timer_duration);
			//default values
	
			//Type-1
			std::string path_texture_1("res/Sprites/enemies/furtive_pink.png");
			t1_enemy_scale = { 0.5f,0.5f };
			std::string path_projectile_texture1("res/Sprites/projectiles/laser_ball_red.png");
			t1_bullet_scale = { 0.4f,0.3f };
		
			//Type
			std::string path_texture_2("res/Sprites/enemies/furtive_emerald.png");
			t2_enemy_scale = { 0.5f,0.5f };
			std::string path_projectile_texture2("res/Sprites/projectiles/laser_ball_purple.png");
			t2_bullet_scale = { 0.4f,0.3f };
			///json data values
			sf::Texture t1_enemy_texture;
			t1_enemy_texture.loadFromFile(path_texture_1);
			sf::Texture t2_enemy_texture;
			t2_enemy_texture.loadFromFile(path_texture_2);
			//projectile textures
			sf::Texture t1_bullet_texture;
			t1_bullet_texture.loadFromFile(path_projectile_texture1);
			sf::Texture t2_bullet_texture;
			t2_bullet_texture.loadFromFile(path_projectile_texture2);

			enemy_textures.emplace_back(t1_enemy_texture);
			enemy_textures.emplace_back(t2_enemy_texture);
			bullet_textures.emplace_back(t1_bullet_texture);
			bullet_textures.emplace_back(t2_bullet_texture);

			t1_speed = 1;
			t2_speed = 1;
		}
		void spawn()override {
			float percent_of_progress = (m_world_pos.x / m_total_length.x) * 100.0f;

			if (percent_of_progress < 20.0f) {

				buffer_alias.emplace_back(new Furtive(t1_health, t1_speed, VectorMath::Vdirection::LEFT));
				//set the texture
				buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);

				//buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
				//set the projectile texture
				buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
				//call set bullet parameters
				buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);

			}
			else if (percent_of_progress < 40.0f) {
				buffer_alias.emplace_back(new Furtive(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
				buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
				buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

			}
			else {
				int range = 1 - 0 + 1;
				int type = rand() % range + 0;

				if (type == 0) {
					//create the enemy
					buffer_alias.emplace_back(new Furtive(t1_health, t1_speed, VectorMath::Vdirection::LEFT));
					//set the texture
					buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);

					//buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
					//set the projectile texture
					buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
					//call set bullet parameters
					buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);

				}
				else {

					buffer_alias.emplace_back(new Furtive(t2_health, t2_speed, VectorMath::Vdirection::LEFT));
					buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
					buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
					buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

				}
			}


			buffer_alias.back()->setPosition(sf::Vector2f(VectorMath::getViewportLowerRightPos().x, SceneManagement::Scene::s_view->getSize().y));

		}
	};
	
	//attacker
	template<> class EnemySpawner<Attacker> :public BaseEnemySpawner {
	public:

		EnemySpawner(std::vector<Enemy*>& enemy_buffer, sf::Vector2f& world_pos, sf::Vector2f& total_length) :BaseEnemySpawner(enemy_buffer, world_pos, total_length) {
			//set the textures
			timer.setDuration(3.0f);




			//default values
			//Type-1
			std::string path_texture_1_1("res/Sprites/enemies/attacker_red_1.png");
			std::string path_texture_1_2("res/Sprites/enemies/attacker_red_2.png");
			t1_enemy_scale = { 0.5f,0.5f };
			std::string path_projectile_texture1("res/Sprites/projectiles/attacker_red_projectile.png");
			t1_bullet_scale = { 0.5f,0.5f };

			//Type-2
			std::string path_texture_2_1("res/Sprites/enemies/attacker_blue_1.png");
			std::string path_texture_2_2("res/Sprites/enemies/attacker_blue_2.png");
			t2_enemy_scale = { 0.5f,0.5f };
			std::string path_projectile_texture2("res/Sprites/projectiles/attacker_blue_projectile.png");
			t2_bullet_scale = { 0.5f,0.5f };
			///json data values
			sf::Texture t1_enemy_texture_1;
			sf::Texture t1_enemy_texture_2;
			t1_enemy_texture_1.loadFromFile(path_texture_1_1);
			t1_enemy_texture_2.loadFromFile(path_texture_1_2);
			sf::Texture t2_enemy_texture_1;
			sf::Texture t2_enemy_texture_2;
			t2_enemy_texture_1.loadFromFile(path_texture_2_1);
			t2_enemy_texture_2.loadFromFile(path_texture_2_2);
			//projectile textures
			sf::Texture t1_bullet_texture;
			t1_bullet_texture.loadFromFile(path_projectile_texture1);
			sf::Texture t2_bullet_texture;
			t2_bullet_texture.loadFromFile(path_projectile_texture2);

			enemy_textures.emplace_back(t1_enemy_texture_1);
			enemy_textures.emplace_back(t1_enemy_texture_2);
			enemy_textures.emplace_back(t2_enemy_texture_1);
			enemy_textures.emplace_back(t2_enemy_texture_2);
			bullet_textures.emplace_back(t1_bullet_texture);
			bullet_textures.emplace_back(t2_bullet_texture);
			t1_speed = 1;
			t2_speed = 1;
		}
		void spawn()override {
			float percent_of_progress = (m_world_pos.x / m_total_length.x) * 100.0f;

			//todo: change this to take array of 2 floats [0.0f,0.0f] as the active spawner range

			if (percent_of_progress < 20.0f) {

				buffer_alias.emplace_back(new Attacker(t1_health, t1_speed, VectorMath::Vdirection::LEFT,&enemy_textures[0],t1_enemy_scale));
				buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
				//call set bullet parameters
				buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);

			}
			else if (percent_of_progress < 40.0f) {
				buffer_alias.emplace_back(new Attacker(t2_health, t2_speed, VectorMath::Vdirection::LEFT,&enemy_textures[1], t2_enemy_scale));
				buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
				buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

			}
			else {
				int range = 1 - 0 + 1;
				int type = rand() % range + 0;

				if (type == 0) {

					buffer_alias.emplace_back(new Attacker(t1_health, t1_speed, VectorMath::Vdirection::LEFT, &enemy_textures[0], t1_enemy_scale));
					buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
					//call set bullet parameters
					buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);

				}
				else {
					buffer_alias.emplace_back(new Attacker(t2_health, t2_speed, VectorMath::Vdirection::LEFT, &enemy_textures[2], t2_enemy_scale));
					buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
					buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

				}
			}


			buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
		}
	};
	//starminator
	template<> class EnemySpawner<Starminator> :public BaseEnemySpawner {
		float t1_rot_speed = 5.0f;
		float t2_rot_speed = 1.0f;
	public:

		EnemySpawner(std::vector<Enemy*>& enemy_buffer, sf::Vector2f& world_pos, sf::Vector2f& total_length) :BaseEnemySpawner(enemy_buffer, world_pos, total_length) {
			//set the textures
			timer.setDuration(5.0f);
			//default values

			//Type-1
			std::string path_texture_1("res/Sprites/enemies/starminator_red.png");
			t1_enemy_scale = { 0.3f,0.3f };
			std::string path_projectile_texture1("res/Sprites/projectiles/laser_ball_red.png");
			t1_bullet_scale = { 0.4f,0.4f };
			
			//Type
			std::string path_texture_2("res/Sprites/enemies/starminator_blue.png");
			t2_enemy_scale = { 0.4f,0.4f };
			std::string path_projectile_texture2("res/Sprites/projectiles/laser_ball_purple.png");
			t2_bullet_scale = { 0.4f,0.3f };
			///json data values
			sf::Texture t1_enemy_texture;
			t1_enemy_texture.loadFromFile(path_texture_1);
			sf::Texture t2_enemy_texture;
			t2_enemy_texture.loadFromFile(path_texture_2);
			//projectile textures
			sf::Texture t1_bullet_texture;
			t1_bullet_texture.loadFromFile(path_projectile_texture1);
			sf::Texture t2_bullet_texture;
			t2_bullet_texture.loadFromFile(path_projectile_texture2);

			enemy_textures.emplace_back(t1_enemy_texture);
			enemy_textures.emplace_back(t2_enemy_texture);
			bullet_textures.emplace_back(t1_bullet_texture);
			bullet_textures.emplace_back(t2_bullet_texture);

			t1_speed = 1;
			t2_speed = 1;
		}
		void spawn()override {
			float percent_of_progress = (m_world_pos.x / m_total_length.x) * 100.0f;
		
			if (percent_of_progress < 20.0f) {

				buffer_alias.emplace_back(new Starminator(t1_health, t1_speed,t1_rot_speed, VectorMath::Vdirection::LEFT));
				//set the texture
				buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);

				//buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
				//set the projectile texture
				buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
				//call set bullet parameters
				buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);

			}
			else if (percent_of_progress < 40.0f) {
				buffer_alias.emplace_back(new Starminator(t2_health, t2_speed, t2_rot_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
				buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
				buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

			}
			else {
				int range = 1 - 0 + 1;
				int type = rand() % range + 0;

				if (type == 0) {

					buffer_alias.emplace_back(new Starminator(t1_health, t1_speed, t1_rot_speed, VectorMath::Vdirection::LEFT));
					//set the texture
					buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);

					//buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
					//set the projectile texture
					buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
					//call set bullet parameters
					buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);
				}
				else {

					buffer_alias.emplace_back(new Starminator(t2_health, t2_speed, t2_rot_speed, VectorMath::Vdirection::LEFT));
					buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
					buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
					buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

				}
			}


			buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);

		}
	};
	//spinner
	template<> class EnemySpawner<Spinner> :public BaseEnemySpawner {
		float t1_rot_speed = 5.0f;
		float t2_rot_speed = 5.0f;
	public:

		EnemySpawner(std::vector<Enemy*>& enemy_buffer, sf::Vector2f& world_pos, sf::Vector2f& total_length) :BaseEnemySpawner(enemy_buffer, world_pos, total_length) {
			//set the textures
			timer.setDuration(7.0f);
			//default values

			//Type-1
			std::string path_texture_1("res/Sprites/enemies/spinner_purple.png");
			t1_enemy_scale = { 0.4f,0.4f };
			std::string path_projectile_texture1("res/Sprites/projectiles/laser_ball_purple.png");
			t1_bullet_scale = { 0.4f,0.4f };

			//Type
			std::string path_texture_2("res/Sprites/enemies/spinner_red.png");
			t2_enemy_scale = { 0.4f,0.4f };
			std::string path_projectile_texture2("res/Sprites/projectiles/laser_ball_red.png");
			t2_bullet_scale = { 0.4f,0.4f };
			///json data values
			sf::Texture t1_enemy_texture;
			t1_enemy_texture.loadFromFile(path_texture_1);
			sf::Texture t2_enemy_texture;
			t2_enemy_texture.loadFromFile(path_texture_2);
			//projectile textures
			sf::Texture t1_bullet_texture;
			t1_bullet_texture.loadFromFile(path_projectile_texture1);
			sf::Texture t2_bullet_texture;
			t2_bullet_texture.loadFromFile(path_projectile_texture2);

			enemy_textures.emplace_back(t1_enemy_texture);
			enemy_textures.emplace_back(t2_enemy_texture);
			bullet_textures.emplace_back(t1_bullet_texture);
			bullet_textures.emplace_back(t2_bullet_texture);

			t1_speed = 7;
			t2_speed = 7;
		}
		void spawn()override {
			float percent_of_progress = (m_world_pos.x / m_total_length.x) * 100.0f;

			if (percent_of_progress < 20.0f) {

				buffer_alias.emplace_back(new Spinner(t1_health, t1_speed, t1_rot_speed, VectorMath::Vdirection::LEFT));
				//set the texture
				buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);

				//buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
				//set the projectile texture
				buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
				//call set bullet parameters
				buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);

			}
			else if (percent_of_progress < 40.0f) {
				buffer_alias.emplace_back(new Spinner(t2_health, t2_speed, t2_rot_speed, VectorMath::Vdirection::LEFT));
				buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
				buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
				buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

			}
			else {
				int range = 1 - 0 + 1;
				int type = rand() % range + 0;

				if (type == 0) {

					buffer_alias.emplace_back(new Spinner(t1_health, t1_speed, t1_rot_speed, VectorMath::Vdirection::LEFT));
					//set the texture
					buffer_alias.back()->setTexture(enemy_textures[0], t1_enemy_scale);

					//buffer_alias.back()->setTexture(t1_enemy_texture, t1_enemy_scale);
					//set the projectile texture
					buffer_alias.back()->setProjectileTexture(bullet_textures[0], t1_bullet_scale);
					//call set bullet parameters
					buffer_alias.back()->setBulletParameters(t1_bullet_damage, t1_bullet_speed);
				}
				else {

					buffer_alias.emplace_back(new Spinner(t2_health, t2_speed, t2_rot_speed, VectorMath::Vdirection::LEFT));
					buffer_alias.back()->setTexture(enemy_textures[1], t2_enemy_scale);
					buffer_alias.back()->setProjectileTexture(bullet_textures[1], t2_bullet_scale);
					buffer_alias.back()->setBulletParameters(t2_bullet_damage, t2_bullet_speed);

				}
			}


			buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);

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
			buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
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

