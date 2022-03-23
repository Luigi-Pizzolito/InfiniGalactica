#include "ShooterLevel.h"
#include "MediaManager/SFXPlayer.h"
#include "Entity/SimpleSpawner.h"
#include <iostream>

#include "SceneManager/SaveSys.h"

ShooterLevel::ShooterLevel(json cfg) :Level(),cfg(cfg)
{
    auto lvlCfg = cfg["levelOptions"];

	total_length.x = (float)lvlCfg["totalLength"];
	//At the start of any level we can set the basic textures, create the player
	//Prepare the vectors for the enemies and bullets
	//Loading textures
	//Reserve Vectors
	prepareContainers();
	//Load 
	loadTextures();
	//Creating  the player
	player = new Player((int)lvlCfg["player"]["health"], (float)lvlCfg["player"]["speed"], (float)lvlCfg["player"]["fric"]);
    int* a = NULL;
    upgrade_points_n = (int)lvlCfg["player"]["upgradePoints"].size();
    upgrade_points = new int[upgrade_points_n];
    for (int i=0; i<upgrade_points_n; i++) {
        upgrade_points[i] = (int)lvlCfg["player"]["upgradePoints"][i];
    }
	//Set player Texture
	player->setTexture(player_textures[(int)lvlCfg["player"]["texture_i"]], sf::Vector2f((float)lvlCfg["player"]["scale"][0],(float)lvlCfg["player"]["scale"][1]));
	
	
	//Create the spawners
	for (auto& spawner_cfg : lvlCfg["spawners"]["enemySpawners"]) {
		spawners.emplace_back(new SimpleSpawner(world_enemies,world_position,total_length, spawner_cfg));
	}
	for (auto& spawner_cfg : lvlCfg["spawners"]["itemSpawners"]) {
		ItemSpawner::addSpawner(item_spawners, world_items, world_position, total_length, spawner_cfg);
	}
	
	
	//create the camera
	camera = new CameraFollowHorzScroll(Scene::s_window,Scene::s_view,player,sf::Vector2f(100.0f,0.0f), (bool)lvlCfg["camera"]["locked"]);
	//create the starfield
	starfield = new StarField(Scene::s_window,Scene::s_view,total_length.x,(int)lvlCfg["starfield"]["starNum"],(float)lvlCfg["starfield"]["nebulaNum"]);
	
	//Set up Timers

	//Music
	music = new MusicPlayer(std::string(lvlCfg["music"]["song"]), true);

	//HUD
	hud = new HUDPanel(Scene::s_window, Scene::s_view, player, &player_score, world_position,total_length);

	portal = new Composit::Portal(s_window, s_view, total_length.x);

	pSc = new PauseSc(s_window, s_view, &paused, cfg["sceneName"]);

    debug_xa = (bool)lvlCfg["debugXa"];
	// std::cout << "Created Level 1\n";
}

ShooterLevel::~ShooterLevel()
{
	//Deletion of Heap allocated variables upon completion of the level or exit of the app
	// std::cout << "Destroyed Level 1\n";
	delete player;
	delete starfield;
	delete camera;
	delete hud;
	delete music;
	delete pSc;
	delete portal;
    delete [] upgrade_points;
    upgrade_points = NULL;
}

//Level Logic
void ShooterLevel::update(float delta_time)
{
	pollEvents();
	if (player->getHP() > 0) {
		if (!paused) {
			
			updateEntities();
			updateEntityCollisions();
			// scroll camera
			camera->follow();

			//check if reached EOL
			if (world_position.x >= total_length.x) {
				SaveSys::saveLevel(cfg["sceneName"], player_score);
				m_finished = true;
			}
		}

		pSc->update();
	}
	else {
		SFX::play(SFXlib::GameOver, 100.0f);
		SaveSys::saveState(cfg["sceneName"]);

		SceneManagement::goToGameOver();
		// SceneManagement::goBackToMainMenu();
	}
	if (m_return) {
		m_return = false;
		SceneManagement::goBackToMainMenu();
	}
}

//Render Level Graphics
void ShooterLevel::render()
{
	// render background
	starfield->draw();

	// renders objects
	for (auto& item_ : world_items) {
		Scene::s_window->draw(item_->getSprite());
	}
	for (auto& enemy : world_enemies) {
		Scene::s_window->draw(enemy->getSprite());
	}
	for (auto& playerbullet : player_bullets) {
		Scene::s_window->draw(playerbullet->getSprite());
	}
	
	for (auto& enemybullet : world_enemy_bullets) {
		Scene::s_window->draw(enemybullet->getSprite());
	}
	Scene::s_window->draw(player->getSprite());

	// EOL Portal
	portal->draw();

	// displays objects on the screen
	hud->draw();
	//Debug
	if (debug_xa) {xa->draw();};

	if (paused) {
		if (pSc->draw()) {
			m_return = true;
		}
	}

	//Transition
	f_in->draw();
}


void ShooterLevel::prepareContainers()
{
    auto pcCfg = cfg["levelOptions"]["prepareContainers"];

	//Reserving Textures
	//Player
	player_textures.reserve((int)pcCfg["textures"]["player"]);
	projectile_textures.reserve((int)pcCfg["textures"]["projectile"]);


	//Reserving Entities and Projectiles
	player_bullets.reserve(pcCfg["bullets"]);
	world_enemies.reserve(pcCfg["enemies"]);
	world_enemy_bullets.reserve(pcCfg["enemyBullets"]);
}

void ShooterLevel::loadTextures()
{
    auto ltCfg = cfg["levelOptions"]["loadTextures"];

	//Player Textures
    for (auto& tex_p : ltCfg["playerTextures"]) {
        player_textures.emplace_back();
        player_textures.back().loadFromFile(std::string(tex_p));
    }

	//Projectile Textures
	//Player
    for (auto& tex_p : ltCfg["projectileTextures"]) {
        projectile_textures.emplace_back();
        projectile_textures.back().loadFromFile(std::string(tex_p));
    }
}


void ShooterLevel::updateEntityCollisions() {
	//Collisions
	//Enemies
	world_enemies.erase(std::remove_if(world_enemies.begin(), world_enemies.end(), [&](Enemy* enemy) {
		//check for collisions with playerbullets
		bool is_dead = false;
		for (size_t i = 0; i < player_bullets.size(); i++) {
			if (enemy->collidesWith(player_bullets[i])) {
				enemy->hurt(player_bullets[i]);
				//deletes the object in the heap
				delete player_bullets[i];
				//deletes the slot that was used for it in the array of bullets
				player_bullets.erase(player_bullets.begin() + i);
			}

		}
		if (enemy->getHP() <= 0) {
			is_dead = true;
			//delete the memory in the heap
			delete enemy;
			player_score += 10;

			SFX::play(SFXlib::EnemyDestroy, 25.0f);
		}

		return is_dead; }), world_enemies.end());
	//items
	world_items.erase(remove_if(world_items.begin(), world_items.end(), [&](GameItem* item_) {
		bool collided=player->collidesWith(item_);
		if (collided) {
			item_->applyEffect(player);
		}
		return collided; }),world_items.end());
	//Player
	world_enemy_bullets.erase(std::remove_if(world_enemy_bullets.begin(), world_enemy_bullets.end(), [&](EnemyBullet* enemy_bullet) {
		bool collided = player->collidesWith(enemy_bullet);
		if (collided) {
			player->hurt(enemy_bullet);
		}

		return collided; }), world_enemy_bullets.end());
}

void ShooterLevel::updateEntities() {
	// Update player score upgrades
	if (!player_max) {
		int tex_i =0;
		for (int i = 0; i<upgrade_points_n; i++) {
			if (player_score > upgrade_points[i]) {
				tex_i=i+1;
				// std::cout << "reached upgrade point: " << upgrade_points[i] << ", upgrades applied: " << tex_i <<"\n";
			}
		}
		// std::cout << "seeting texture to: " << tex_i << "\n";
		player->upgrade(tex_i);
		player->setTexture(player_textures[tex_i]);
		if (player_score > upgrade_points[upgrade_points_n-1]) {
			player_max = true;
		}
	}

	// Update Player physics
	player->updatePhysics();
	updateWorldPosition();

	// Update spawners, enemies and bullets
	for (auto& spawner : spawners) {
		spawner->update();
	}
	for (auto& itemspawner : item_spawners) {
		itemspawner->update();
	}
	//Entities and projectiles actions
	for (auto& playerbullet : player_bullets) {

		playerbullet->move();

	}
	for (auto& enemy : world_enemies) {
		enemy->move();
		if (enemy->canShoot()) {
			spawnEnemyBullet(enemy);
		}
	}
	for (auto& enemybullet : world_enemy_bullets) {
		enemybullet->move();
	}

	//Update music loops with world position
	float levelProgress =world_position.x/total_length.x;
	music->update(levelProgress);

	// Collectors
	for (auto& collector : collectors) {
		collector->update();
	}
}