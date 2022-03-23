#include "BossLevel3.h"
#include "MediaManager/SFXPlayer.h"
BossLevel3::BossLevel3(json cfg):cfg(cfg)
{
	
	boss = new CommanderStarminator(300, 10, 5, VectorMath::Vdirection::UP);
	mines_timer.setDuration(5.0f);
	//Reserve Vectors
	boss_health.x = boss->getHP();
	prepareContainers();
	//Load 
	loadTextures();
	//spawnMines();
	Scene::s_window->setView(*Scene::s_view);
	player = new Player(100, 0.5f, 100.0f);
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

	boss_texture.loadFromFile("res/Sprites/enemies/bosses/BossStarminator.png");
	boss->setTexture(boss_texture, sf::Vector2f(0.7f, 0.7f));
	boss->setPosition(VectorMath::getViewportLowerRightPos() - sf::Vector2f(boss->getSize().x, Scene::s_view->getSize().y) / 2.0f);
	boss->setProjectileTexture(boss_projectile_texture, sf::Vector2f(1.0f, 1.0f));
	boss->setBulletParameters(1,20);

	f_in = new Composit::Fade(s_window, s_view, false, 4);
	f_in->trigger();

}

BossLevel3::~BossLevel3()
{
	delete player;
	delete r_starfield;
	delete camera;
	delete hud;
	delete music;
	delete boss;
	delete pSc;
}

void BossLevel3::update(float delta_time)
{
	pollEvents();

	if (player->getHP() > 0) {
		if (!paused) {
		if (boss_health.x <= 0) {
			//? next lvl
			Scene::s_view->zoom(1.0f/1.8f);
			Scene::s_window->setView(*Scene::s_view);
			SaveSys::saveLevel(cfg["sceneName"], player_score);
			m_finished = true; //? goto next level
			// m_return = true;

		}
		else {
			if (mines_timer.timeOut()) {
				spawnMines();
			}
			camera->follow();
			updateEntityCollisions();
			updateEntities();

		}

		//spawners
		//for (auto& spawner : spawners) {
		//	spawner->update();
		//}


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

void BossLevel3::render()
{
	r_starfield->draw();
	Scene::s_window->draw(boss->getSprite());
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

void BossLevel3::prepareContainers()
{
	player_textures.reserve(3);
	projectile_textures.reserve(3);
	//Reserving Entities and Projectiles
	player_bullets.reserve(80);
	world_enemies.reserve(150);
	world_enemy_bullets.reserve(300);

}

void BossLevel3::loadTextures()
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
	boss_projectile_texture.loadFromFile("res/Sprites/projectiles/laser_ball_purple.png");
	mines_texture.loadFromFile("res/Sprites/projectiles/laser_ball_red.png");

}

void BossLevel3::updateEntityCollisions()
{
	//Collisions
	//Boss
	for (size_t i = 0; i < player_bullets.size(); i++) {
		if (boss->collidesWith(player_bullets[i])) {
			boss->hurt(player_bullets[i]);
			//deletes the object in the heap
			delete player_bullets[i];
			//deletes the slot that was used for it in the array of bullets
			player_bullets.erase(player_bullets.begin() + i);
		}
	}
	boss_health.x = boss->getHP();
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

void BossLevel3::updateEntities()
{

	boss->updateStates();
	player->updatePhysics();
	boss->lookAt(player->getCenterPos());
	if (boss->canShoot()) {
		spawnEnemyBullet(boss);
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
	static float increment = 0.0f;
	for (auto& bullet : world_enemy_bullets) {
		
		bullet->setSpeed(increment);
		bullet->move();
		bullet->rotate(5);
		increment += 0.01f;

	}
	if (world_enemy_bullets.size() < 1) {
		mines_timer.start();
		increment = 0.0f;
	}

}

void BossLevel3::spawnMines()
{
	
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_real_distribution <float> x_distr(0, 20);
	std::uniform_int_distribution<int> v_distr(-100, 100);
	for (size_t i = 0; i < Scene::s_view->getSize().x * 1.8; i += 100) {

		for (size_t j = 0; j < Scene::s_view->getSize().y * 1.8; j += 100) {
			if (x_distr(generator) > 16) {
				world_enemy_bullets.emplace_back(new EnemyBullet(5, 10, sf::Vector2f(i, j), VectorMath::getUnitaryVector(sf::Vector2f(v_distr(generator),v_distr(generator)))));
				world_enemy_bullets.back()->setTexture(mines_texture, sf::Vector2f(1.0f, 1.0f));

			}

		}


	}

	can_spawn = false;

}

