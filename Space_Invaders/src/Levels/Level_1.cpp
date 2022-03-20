#include "Level_1.h"
#include "MediaManager/SFXPlayer.h"

Level1::Level1() :Level()
{
	total_length.x = 50.0f;
	//At the start of any level we can set the basic textures, create the player
	//Prepare the vectors for the enemies and bullets
	//Loading textures
	//Reserve Vectors
	prepareContainers();
	//Load 
	loadTextures();
	//Creating  the player
	player = new Player(100, 0.5f, 100.0f);
	//Set player Texture
	player->setTexture(player_textures[0], sf::Vector2f(0.5f,0.5f));
	//create the camera
	camera = new CameraFollowHorzScroll(Scene::s_window,Scene::s_view,player,sf::Vector2f(100.0f,0.0f));
	//create the starfield
	starfield = new StarField(Scene::s_window,Scene::s_view,25,1.4f);
	//Screen Effect
	
	//Set up Timers
	screen_effect.setSize(sf::Vector2f(Scene::s_window->getSize().x, Scene::s_window->getSize().y));
	screen_effect.setOrigin(screen_effect.getSize().x / 2, screen_effect.getSize().y / 2);
	screen_effect.setPosition(Scene::s_view->getCenter());
	screen_effect.setFillColor(sf::Color(255, 255, 255, 0));
	screen_effect.setTexture(&broken_screen_texture);

	//Music
	music = new MusicPlayer("song1", true);

	//HUD
	hud = new HUDPanel(Scene::s_window, Scene::s_view, player, &player_score, world_position,total_length);

	// std::cout << "Created Level 1\n";
}

Level1::~Level1()
{
	//Deletion of Heap allocated variables upon completion of the level or exit of the app
	// std::cout << "Destroyed Level 1\n";
	delete player;
	delete starfield;
	delete camera;
	delete hud;
	delete music;
}

//Level Logic
void Level1::update(float delta_time)
{
	pollEvents();
	if (player->getHP() > 0) {
		if (player_score > 40 && !player_max) {
			player->setTexture(player_textures[1], sf::Vector2f(0.5f, 0.5f));
			player_max = true;
			player->upgrade();
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

				SFX::play(SFXlib::EnemyDestroy);
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


				// for testing music access
				if (player->getHP() <=0) {
					music->stop();
				}
			}

			return collided; }), world_enemy_bullets.end());

		// scroll camera
		camera->follow();

		// Collectors
		for (auto& collector : collectors) {
			collector->update();
		}
		//check if reached EOL
		if (world_position.x >= total_length.x-((VectorMath::getViewportLowerRightPos().x-VectorMath::getViewPortTopLeftPos().x)/100.0f)) {
			m_finished = true;
		}
	}
	else {
		
		screen_effect.setPosition(Scene::s_view->getCenter());
		screen_effect.setFillColor(sf::Color(255, 255, 255, 255));
		SceneManagement::goBackToMainMenu();
	}

	//Update music loops with world position
	float levelProgress =world_position.x/total_length.x;
	music->update(levelProgress);
}

//Render Level Graphics
void Level1::render()
{
	// render background
	starfield->draw();

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
	Scene::s_window->draw(screen_effect);
	// displays objects on the screen
	hud->draw();
	//Debug
	xa->draw();
}


void Level1::prepareContainers()
{
	//Reserving Textures
	//Player
	player_textures.reserve(3);
	projectile_textures.reserve(3);


	//Reserving Entities and Projectiles
	player_bullets.reserve(80);
	world_enemies.reserve(50);
	world_enemy_bullets.reserve(80);
	


}

void Level1::loadTextures()
{
	//Player Textures
	player_textures.emplace_back();
	player_textures.back().loadFromFile("res/Sprites/player/player_base.png");
	player_textures.emplace_back();
	player_textures.back().loadFromFile("res/Sprites/player/player_upgrade_1.png");

	//Projectile Textures
	//Player
	projectile_textures.emplace_back();
	projectile_textures.back().loadFromFile("res/Sprites/projectiles/laser_red.png");
	//Screen Effect
	broken_screen_texture.loadFromFile("res/Sprites/effects/brokenscreen.png");
}


