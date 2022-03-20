#pragma once
#include "SceneManager/Scene.h"
#include "MediaManager/MusicPlayer.h"
#include "Application/Application.h"
#include <vector>
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Projectiles/Projectile.h"
#include "MediaManager/MusicPlayer.h"
#include "MediaManager/HUDPanel.h"
#include "Algorithms/StarField.h"
#include "Algorithms/CameraFollowScroll.h"
#include "Algorithms/Utilities.h"
#include "Algorithms/MathUtils.h"
#include "Algorithms/MemoryManegement.h"

class Level :public SceneManagement::Scene {
protected:
	//variables
	size_t player_score;
	size_t enemy_death_count;
	bool player_max;
	//Textures,since we aren't sure how many types of enemies we need per level,
	//it is more convenient to use a vector
	std::vector<sf::Texture> player_textures;

	std::vector<sf::Texture> projectile_textures;
	std::vector<sf::Texture> enemy_projectile_texture;

	//Entities
	Player* player;
	//this handles the bullet slot based on the available type of bullet
	uint8_t selected_slot;
	//In the future subdivide this into enemy type1 type2
	std::vector<Enemy*> world_enemies;
	std::vector<MemoryManagement::BaseEnemySpawner*> spawners;
	//Projectiles
	std::vector<PlayerBullet*> player_bullets;
	std::vector<EnemyBullet*> world_enemy_bullets;
	//Collectors
	std::vector<MemoryManagement::BasicCollector*> collectors;

	//HUD
	HUDPanel* hud;
	//Background
	StarField* starfield;
	//Camera
	CameraFollowHorzScroll* camera;

	//Key states
	bool key_u;
	bool key_d;
	bool key_l;
	bool key_r;
	bool key_s;
	//timers and spawners
	
	

	//Music
	MusicPlayer* music;

	//Effects
	sf::Texture broken_screen_texture;
	sf::RectangleShape screen_effect;

	//Debug
	Debug::XAxis* xa;

protected:
	//methods
	void pollEvents()override;
	//we update and render are not needed here
	virtual void prepareContainers(){}
	virtual void loadTextures(){}

	void playerInputStates(STATES state);
	void switchSlot();
	void spawnPlayerBullet();
	void spawnEnemyBullet(Enemy* enemy);

public:
	Level();
	virtual~Level();

};

