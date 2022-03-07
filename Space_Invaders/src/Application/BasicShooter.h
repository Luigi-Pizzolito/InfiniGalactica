#pragma once
#include "Application.h"
#include <vector>
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Algorithms/StarField.h"
#include "Algorithms/CameraFollowScroll.h"
#include "Algorithms/Utilities.h"


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

	//In the future subdivide this into enemy type1 type2
	std::vector<Enemy*> world_enemies;
	//Projectiles
	std::vector<PlayerBullet*> player_bullets;
	std::vector<EnemyBullet*> world_enemy_bullets;

	//Background
	StarField starfield;

	//Camera
	CameraFollowHorzScroll camera;

	//Key states
	bool key_u;
	bool key_d;
	bool key_l;
	bool key_r;
	bool key_s;

	//timers and spawners
	Control::GameTimer player_bullet_timer;
	Control::GameTimer enemy_spawner;

public:
	//Constructors and Destructors
	ShooterGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~ShooterGame();
	void pollEvents()override;
	void update()override;
	void render()override;
private:
	void playerInputState(STATES state);
	void SpawnEnemy(const sf::Vector2f& position);
	void SpawnPlayerBullet();
	void SpawnEnemyBullet();

};
