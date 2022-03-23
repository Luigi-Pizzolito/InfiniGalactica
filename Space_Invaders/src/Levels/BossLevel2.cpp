#include "BossLevel2.h"
#include "MediaManager/SFXPlayer.h"

#include <json.hpp>
using json = nlohmann::json;

BossLevel2::BossLevel2(json cfg):cfg(cfg)
{
	current_boss = 0;
	max_enemy_count = 10;
	boss.reserve(2);
	boss.emplace_back(50, 10, VectorMath::Vdirection::UP,4.0f);
	boss.emplace_back(50, 20, VectorMath::Vdirection::UP,2.0f);
	boss_health = sf::Vector2f(boss.front().getHP()+boss.back().getHP(), 0.0f);
	//Reserve Vectors
	prepareContainers();
	
	// minion spawners
	json spawner_cfg1 = "{\"spawn_type\":\"Attacker\",\"spawn_range\":[0.0,0.0],\"member\":{\"health\":20,\"speed\":1.0,\"timer\":3.0,\"scale\":[0.5,0.5],\"bullet\":{\"damage\":20,\"speed\":15,\"scale\":[0.5,0.5],\"textures\":[\"res/Sprites/projectiles/attacker_red_projectile.png\"]},\"textures\":[\"res/Sprites/enemies/attacker_red_1.png\",\"res/Sprites/enemies/attacker_red_2.png\"]}}"_json;
	json spawner_cfg2 = "{\"spawn_type\":\"Attacker\",\"spawn_range\":[0.0,0.0],\"member\":{\"health\":30,\"speed\":5.0,\"timer\":3.0,\"scale\":[0.5,0.5],\"bullet\":{\"damage\":10,\"speed\":15,\"scale\":[0.5,0.5],\"textures\":[\"res/Sprites/projectiles/attacker_blue_projectile.png\"]},\"textures\":[\"res/Sprites/enemies/attacker_blue_1.png\",\"res/Sprites/enemies/attacker_blue_2.png\"]}}"_json;
	spawners.emplace_back(new SimpleSpawner(world_enemies,world_position,total_length, spawner_cfg1));
	spawners.emplace_back(new SimpleSpawner(world_enemies,world_position,total_length, spawner_cfg2));
	
	//Load 
	loadTextures();
	Scene::s_window->setView(*Scene::s_view);
	player = new Player(1000, 0.5f, 100.0f);
	//Set player Texture
	player->setTexture(player_textures[0], sf::Vector2f(0.5f, 0.5f));
	//create the camera
	Scene::s_view->zoom(1.8f);
	camera = new CameraFollowHorzScroll(Scene::s_window, Scene::s_view, player, sf::Vector2f(100.0f, 0.0f), true);
	//create the starfield
	// starfield = new starfield(Scene::s_window, Scene::s_view, s_view->getSize().x, 25, 1.4f);
	r_starfield = new RadialStarField(Scene::s_window, Scene::s_view, 350, 8);
	hud = new HUDPanel(Scene::s_window, Scene::s_view, player, &player_score, boss_health, boss_health, 0.8f);
	//Music
	music = new MusicPlayer("song5", true);

	pSc = new PauseSc(s_window, s_view, &paused, cfg["sceneName"]);
	//First boss
	boss_texture[0].loadFromFile("res/Sprites/enemies/bosses/BossAttacker_purple.png");
	boss.front().setTexture(boss_texture[0], sf::Vector2f(1.0f, 1.0f));
	boss.front().setPosition(VectorMath::getViewportLowerRightPos() - sf::Vector2f(-boss.front().getSize().x, Scene::s_view->getSize().y) / 2.0f);
	boss.front().setProjectileTexture(boss_projectile_texture[0], sf::Vector2f(0.3f, 0.3f));
	boss.front().setBulletParameters(1, 10);

	//Second boss
	boss_texture[1].loadFromFile("res/Sprites/enemies/bosses/BossAttacker_green.png");
	boss.back().setTexture(boss_texture[1], sf::Vector2f(1.0f, 1.0f));
	boss.back().setPosition(VectorMath::getViewportLowerRightPos() - sf::Vector2f(-boss.back().getSize().x, Scene::s_view->getSize().y) / 2.0f);
	boss.back().setProjectileTexture(boss_projectile_texture[1], sf::Vector2f(0.3f, 0.3f));
	boss.back().setBulletParameters(1, 20);


	f_in = new Composit::Fade(s_window, s_view, false, 4);
	f_in->trigger();

}

BossLevel2::~BossLevel2()
{
	delete player;
	delete r_starfield;
	delete camera;
	delete hud;
	delete music;
	delete pSc;

}

void BossLevel2::update(float delta_time)
{
	pollEvents();
	if (player->getHP() > 0) {
		if (!paused) {
		if (boss_health.x <= 0) {
			//? next lvl
			//!placeholder for finishing the level
			Scene::s_view->zoom(1.0f/1.8f);
			Scene::s_window->setView(*Scene::s_view);
			SaveSys::saveLevel(cfg["sceneName"], player_score);
			m_finished = true; //? goto next level

		}
		else {
			camera->follow();
			updateEntityCollisions();
			updateEntities();

		}
		//spawners
		for (auto& spawner : spawners) {
			spawner->update();
		}


		for (auto& collector : collectors) {
			collector->update();
		}
		}
		pSc->update();

	}
	else {

		//!game over
		Scene::s_view->zoom(1.0f/1.8f);
		Scene::s_window->setView(*Scene::s_view);
		SaveSys::saveState(cfg["sceneName"]);
		SFX::play(SFXlib::GameOver, 100.0f);
		SceneManagement::goToGameOver();

	}
	if (m_return) {
		//! exit level
		m_return = false;
		Scene::s_view->zoom(1.0f / 1.8f);
		Scene::s_window->setView(*Scene::s_view);
		SceneManagement::goBackToMainMenu();
	}
}

void BossLevel2::render()
{
	r_starfield->draw();
	Scene::s_window->draw(boss[current_boss].getSprite());
	// renders objects
	for (auto& enemy : world_enemies) {
		Scene::s_window->draw(enemy->getSprite());
	}
	for (auto& playerbullet : player_bullets) {
		Scene::s_window->draw(playerbullet->getSprite());
	}
	for (auto& item_ : world_items) {
		Scene::s_window->draw(item_->getSprite());
	}
	for (auto& enemybullet : world_enemy_bullets) {
		Scene::s_window->draw(enemybullet->getSprite());
	}
	Scene::s_window->draw(player->getSprite());
	// displays objects on the screen
	hud->draw();

	if (paused) {
		if (pSc->draw()) {
			m_return = true;
		}
	}

	//Transition
	f_in->draw();
}

void BossLevel2::prepareContainers()
{
	player_textures.reserve(3);
	projectile_textures.reserve(3);
	//Reserving Entities and Projectiles
	player_bullets.reserve(80);
	world_enemies.reserve(150);
	world_enemy_bullets.reserve(300);

}

void BossLevel2::loadTextures()
{
	//Player Textures
	player_textures.emplace_back();
	player_textures.back().loadFromFile("res/Sprites/player/player_base.png");
	player_textures.emplace_back();
	player_textures.back().loadFromFile("res/Sprites/player/player_upgrade_1.png");

	//Projectile Textures
	//Players
	projectile_textures.emplace_back();
	projectile_textures.back().loadFromFile("res/Sprites/projectiles/laser_red.png");
	//boss1
	boss_projectile_texture[0].loadFromFile("res/Sprites/projectiles/laser_purple.png");
	//boss2
	boss_projectile_texture[1].loadFromFile("res/Sprites/projectiles/laser_green.png");

}

void BossLevel2::updateEntityCollisions()
{
	//Collisions
	//Boss
	for (size_t i = 0; i < player_bullets.size(); i++) {
		if (boss[current_boss].collidesWith(player_bullets[i])) {
			boss[current_boss].hurt(player_bullets[i]);
			//deletes the object in the heap
			delete player_bullets[i];
			//deletes the slot that was used for it in the array of bullets
			player_bullets.erase(player_bullets.begin() + i);
		}
	}
	//Minions
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

			SFX::play(SFXlib::EnemyDestroy);
		}

		return is_dead; }), world_enemies.end());
	//items
	world_items.erase(remove_if(world_items.begin(), world_items.end(), [&](GameItem* item_) {
		bool collided = player->collidesWith(item_);
		if (collided) {
			item_->applyEffect(player);
		}
		return collided; }), world_items.end());
	//Player
	world_enemy_bullets.erase(std::remove_if(world_enemy_bullets.begin(), world_enemy_bullets.end(), [&](EnemyBullet* enemy_bullet) {
		bool collided = player->collidesWith(enemy_bullet);
		if (collided) {
			player->hurt(enemy_bullet);


			// for testing music access
			if (player->getHP() <= 0) {
				music->stop();
			}
		}

		return collided; }), world_enemy_bullets.end());
}

void BossLevel2::updateEntities()
{
	if (boss[current_boss].isInPosition()) {
		if (current_boss <= boss.size()) {
			current_boss++;
		}
	}
	boss[current_boss].updateStates();
	boss_health.x = boss.front().getHP() + boss.back().getHP();
	player->updatePhysics();

	if (boss[current_boss].canShoot()) {
		spawnEnemyBullet(&boss[current_boss]);

	}
	//enemies
	for (auto& enemy : world_enemies) {
		enemy->move();
		if (enemy->canShoot()) {
			spawnEnemyBullet(enemy);
		}
	}

	//bullets
	for (auto& bullet : player_bullets) {
		bullet->move();
	}
	for (auto& bullet : world_enemy_bullets) {
		bullet->move();
	}

}


