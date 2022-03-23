#pragma once
#include <vector>
#include <string>
#include "SceneManager/Scene.h"
#include "Algorithms/Utilities.h"
#include "Algorithms/MathUtils.h"
#include "GameItems/GameItem.h"
#include "Entity/Enemy.h"
// #include <iostream>

class Enemy;
class GameItem;

class SimpleSpawner {
    protected:
        //initialisers
        std::vector<Enemy*>& buffer_alias;
        sf::Vector2f& m_world_pos;
        sf::Vector2f& m_total_length;
        //json param
        json cfg;
        sf::Vector2f spawn_range;
        std::string spawn_type;
        //spawning member params
        //textures
        std::vector<sf::Texture> enemy_textures;
        std::vector<sf::Texture> bullet_textures;
        //enemy params
        uint8_t speed;
        uint16_t health;
        Control::GameTimer timer;
        float timer_duration;
        sf::Vector2f enemy_scale;
        sf::Vector2f bullet_scale;
        uint8_t bullet_damage;
        uint8_t bullet_speed;
        //optional params for specific types
        float rot_speed;
    public:
        SimpleSpawner(std::vector<Enemy*>& enemy_buffer,sf::Vector2f& world_pos,sf::Vector2f& total_length, json cfg) :
        buffer_alias(enemy_buffer),m_world_pos(world_pos),m_total_length(total_length),cfg(cfg) {
            // std::cout << "new spawner with: " << cfg.dump() << "\n";
            //initilise from JSON + spawn range
            spawn_type = std::string(cfg["spawn_type"]);
            spawn_range = sf::Vector2f((float)cfg["spawn_range"][0], (float)cfg["spawn_range"][1]);
            auto member = cfg["member"];
            // spawning member params
            health = (uint16_t)member["health"];
            speed = (uint8_t)member["speed"];
            timer.setDuration((float)member["timer"]);
            enemy_scale = sf::Vector2f((float)member["scale"][0], (float)member["scale"][1]);
            bullet_damage = (uint8_t)member["bullet"]["damage"];
            bullet_speed = (uint8_t)member["bullet"]["speed"];
            bullet_scale = sf::Vector2f((float)member["bullet"]["scale"][0],(float)member["bullet"]["scale"][1]);
            //iterate over add textures
            for (auto& p_tex : member["textures"]) {
                sf::Texture enemy_texture;
                enemy_texture.loadFromFile(std::string(p_tex));
                enemy_textures.emplace_back(enemy_texture);
            }
            for (auto& b_tex : member["bullet"]["textures"]) {
                sf::Texture bullet_texture;
                bullet_texture.loadFromFile(std::string(b_tex));
                bullet_textures.emplace_back(bullet_texture);
            }
            //optional params
            if (cfg["spawn_type"] == "Starminator" || cfg["spawn_type"] == "Spinner") {
                rot_speed = (float)member["rot_speed"];
            }
        }

        ~SimpleSpawner() {

        }

        void update() {
            timer.start();
            if (timer.timeOut()) {
                if ( spawn_type == "Enemy" ) {
                    spawn<Enemy>();
                } else
                if ( spawn_type == "Furtive" ) {
                    spawn<Furtive>();
                } else
                if ( spawn_type == "Attacker" ) {
                    spawn<Attacker>();
                } else
                if ( spawn_type == "Starminator" ) {
                    spawn<Starminator>();
                } else
                if ( spawn_type == "Spinner" ) {
                    spawn<Spinner>();
                }
            }
        }

        template<typename T>
        void spawn() {
            float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;
            //if spawner in active range
            if ( percent_of_progress > spawn_range.x && percent_of_progress < spawn_range.y || spawn_range.y == 0.0f ) {
                buffer_alias.emplace_back(new T(health, speed, VectorMath::Vdirection::LEFT));
                //set the texture
                buffer_alias.back()->setTexture(enemy_textures[0], enemy_scale);
                //set the projectile texture
                buffer_alias.back()->setProjectileTexture(bullet_textures[0], bullet_scale);
                //call set bullet parameters
                buffer_alias.back()->setBulletParameters(bullet_damage, bullet_speed);

                buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
            }
        }

        //overide spawner params func spawn for Attacker (2 textures), Starminator (rot_speed), Spinner (rot_speed)
        template<> void spawn<Attacker>() {
            float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;
            //if spawner in active range
            if ( percent_of_progress > spawn_range.x && percent_of_progress < spawn_range.y || spawn_range.y == 0.0f ) {
                buffer_alias.emplace_back(new Attacker(health, speed, VectorMath::Vdirection::LEFT, &enemy_textures[0], enemy_scale));
                //set the texture
                // buffer_alias.back()->setTexture(enemy_textures[0], enemy_scale);
                //set the projectile texture
                buffer_alias.back()->setProjectileTexture(bullet_textures[0], bullet_scale);
                //call set bullet parameters
                buffer_alias.back()->setBulletParameters(bullet_damage, bullet_speed);

                buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
            }
        }

        template<> void spawn<Starminator>() {
            float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;
            //if spawner in active range
            if ( percent_of_progress > spawn_range.x && percent_of_progress < spawn_range.y || spawn_range.y == 0.0f ) {
                buffer_alias.emplace_back(new Starminator(health, speed, rot_speed, VectorMath::Vdirection::LEFT));
                //set the texture
                buffer_alias.back()->setTexture(enemy_textures[0], enemy_scale);
                //set the projectile texture
                buffer_alias.back()->setProjectileTexture(bullet_textures[0], bullet_scale);
                //call set bullet parameters
                buffer_alias.back()->setBulletParameters(bullet_damage, bullet_speed);

                buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
            }
        }

        template<> void spawn<Spinner>() {
            float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;
            //if spawner in active range
            if ( percent_of_progress > spawn_range.x && percent_of_progress < spawn_range.y || spawn_range.y == 0.0f ) {
                buffer_alias.emplace_back(new Spinner(health, speed, rot_speed, VectorMath::Vdirection::LEFT));
                //set the texture
                buffer_alias.back()->setTexture(enemy_textures[0], enemy_scale);
                //set the projectile texture
                buffer_alias.back()->setProjectileTexture(bullet_textures[0], bullet_scale);
                //call set bullet parameters
                buffer_alias.back()->setBulletParameters(bullet_damage, bullet_speed);

                buffer_alias.back()->setPosition(VectorMath::getViewportLowerRightPos().x);
            }
        }
};



//!! this has not been parametrised to spawn different items with a base class, implement if needd.
class BaseItemSpawner{
    protected:
        std::vector<GameItem*>& buffer_alias;
        sf::Vector2f& m_world_pos;
        sf::Vector2f& m_total_length;
        Control::GameTimer timer;
        sf::Texture health_package_texture;
        sf::Texture fire_rate_booster_texture;
        sf::Texture damage_booster_texture;
        //only one scale because our current textures have the same size
        //if we change to different textures, then set different scales
        sf::Vector2f general_scale;
        sf::Vector2f spawn_range;
    public:
        BaseItemSpawner(std::vector<GameItem*>& item_buffer, sf::Vector2f& world_pos,sf::Vector2f& total_length, json cfg) :buffer_alias(item_buffer),m_world_pos(world_pos),m_total_length(total_length) {
            spawn_range = sf::Vector2f((float)cfg["spawn_range"][0], (float)cfg["spawn_range"][1]);
            timer.setDuration((float)cfg["timer"]);
            general_scale = sf::Vector2f((float)cfg["item_scale"][0], (float)cfg["item_scale"][1]);

            std::string health_package_path("res/Sprites/items/health_package.png");
            std::string fire_rate_booster_path("res/Sprites/items/fire_rate_booster.png");
            std::string damage_booster_path("res/Sprites/items/damage_booster.png");
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
            float percent_of_progress=(m_world_pos.x/m_total_length.x)*100.0f;
            //if spawner in active range
            if ( percent_of_progress > spawn_range.x && percent_of_progress < spawn_range.y || spawn_range.y == 0.0f ) {
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
        }

};

class ItemSpawner {
    public:
        ItemSpawner() {}
        ~ItemSpawner() {}

        static void addSpawner(std::vector<BaseItemSpawner*>& item_spawners, std::vector<GameItem*>& item_buffer, sf::Vector2f& world_pos,sf::Vector2f& total_length, json cfg) {
            if (cfg["spawn_type"] == "base_items") {
                item_spawners.emplace_back(new BaseItemSpawner(item_buffer, world_pos, total_length, cfg));
            }
        }
};