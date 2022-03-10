#pragma once
#include "Application.h"
#include <vector>
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Algorithms/StarField.h"
#include "Algorithms/CameraFollowScroll.h"
#include "Algorithms/Utilities.h"

//Class Implemented by Daniel 02.27 10:00 AM
class ShooterGame :public Application {
	//Implemented by Daniel 02.27 10:01 AM
private:
	//Game variables (Needs more abstraction, implement a scene class)
	int player_score;
	//Textures
	sf::Texture player_texture;
	sf::Texture enemy_texture;
	sf::Texture projectile_texture;
	sf::Texture broken_screen;
	//Entities
	Player player;
	//Implemented by Daniel 02.27 10:02 AM
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
	//Implemented by Daniel 03.07 10:00 AM
	bool key_s;

	//timers and spawners
	Control::GameTimer player_bullet_timer;
	Control::GameTimer enemy_spawner;
	sf::RectangleShape rectangle;
public:
	//Constructors and Destructors
	ShooterGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~ShooterGame();
	//Added by Daniel 02.27 11:00 AM
	void pollEvents()override;
	void update()override;
	void render()override;
private:
	//Added by Daniel 03.03 1:55 PM
	void playerInputState(STATES state);
	//Added by Daniel 03.05 2:44 PM
	void SpawnEnemy(const sf::Vector2f& position);
	void SpawnPlayerBullet();
	void SpawnEnemyBullet(const sf::Vector2f& position, const sf::Vector2f dir);

};
