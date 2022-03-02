#pragma once
#include "Application.h"
#include <vector>
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Projectiles/Projectile.h"

//Example for Conways Game of Life
class ShooterGame :public Application {

private:
	//Game variables (Needs more abstraction, implement a scene class)
	int player_score;
	//Textures
	sf::Texture player_texture;
	sf::Texture enemy_texture;
	sf::Texture projectile_texture;
	//Entities
	Player player;
	std::vector<Enemy> world_enemies;
	//Projectiles
	std::vector<PlayerBullet> player_bullets;
	std::vector<EnemyBullet> world_enemy_bullets;

	#ifdef __APPLE__
	bool key_u;
	bool key_d;
	bool key_l;
	bool key_r;
	#endif

public:
	//Constructors and Destructors
	ShooterGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~ShooterGame();
	void pollEvents()override;
	void update()override;
	void render()override;
private:
	void SpawnEnemy();
	void SpawnPlayerBullet();
	void SpawnEnemyBullet();

};