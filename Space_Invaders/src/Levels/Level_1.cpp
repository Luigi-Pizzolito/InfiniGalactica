#include "Level_1.h"

Level1::Level1() :Level()
{
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
	player->setTexture(player_textures[0]);
	//create the camera
	camera = new CameraFollowHorzScroll(Scene::s_window,Scene::s_view,player,sf::Vector2f(100.0f,0.0f));
	//create the starfield
	starfield = new StarField(Scene::s_window,Scene::s_view,25,1.4f);
	//Screen Effect
	
	//Set up Timers
	setUpTimers();
	screen_effect.setSize(sf::Vector2f(Scene::s_window->getSize().x, Scene::s_window->getSize().y));
	screen_effect.setOrigin(screen_effect.getSize().x / 2, screen_effect.getSize().y / 2);
	screen_effect.setPosition(Scene::s_view->getCenter());
	screen_effect.setFillColor(sf::Color(255, 255, 255, 0));
	screen_effect.setTexture(&broken_screen_texture);

	//Music
	music = new MusicPlayer("song1", true);
}

Level1::~Level1()
{
	//Deletion of Heap allocated variables upon completion of the level or exit of the app
	delete player;
	delete starfield;
	delete camera;
	// delete music;
}

//Level Logic
void Level1::update(float delta_time)
{
	pollEvents();
	if (player->getHP() > 0) {
		if (player_score > 100) {
			player->setTexture(player_textures[1]);
		}
		// Update Player physics
		player->updatePhysics();


		// Update spawners, enemies and bullets
		player_bullet_timer.start();
		enemy_spawner.start();
		if (enemy_spawner.timeOut()) {
			//calculate the position
			//if some problem change the second sview to swindow
			sf::Vector2f pos(Scene::s_view->getCenter().x + Scene::s_view->getSize().x / 2,
				Scene::s_view->getSize().y);

			spawnEnemy(pos);
		}

		//Entities and projectiles actions
		for (auto& playerbullet : player_bullets) {

			playerbullet->move();

		}
		for (auto& enemy : world_enemies) {
			enemy->move();
			if (enemy->canShoot()) {
				spawnEnemyBullet(enemy_projectile_texture[0],VectorMath::getAABBMidBack(enemy->getTopLeftPos(), enemy->getSize()), VectorMath::Vdirection::LEFT);

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
			}

			return is_dead; }), world_enemies.end());
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

	}
	else {
		
		screen_effect.setPosition(Scene::s_view->getCenter());
		screen_effect.setFillColor(sf::Color(255, 255, 255, 255));
	}

	//todo: update music with level progress %
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
	for (auto& enemybullet : world_enemy_bullets) {
		Scene::s_window->draw(enemybullet->getSprite());
	}
	Scene::s_window->draw(player->getSprite());
	Scene::s_window->draw(screen_effect);
	// displays objects on the screen
}


void Level1::prepareContainers()
{
	//Reserving Textures
	//Player
	player_textures.reserve(3);
	projectile_textures.reserve(3);
	//Enemy
	enemy_textures.reserve(3);
	enemy_projectile_texture.reserve(2);

	//Reserving Entities and Projectiles
	player_bullets.reserve(80);
	world_enemies.reserve(50);
	world_enemy_bullets.reserve(80);
	


}

void Level1::loadTextures()
{
	//Player Textures
	player_textures.emplace_back();
	player_textures.back().loadFromFile("res/Sprites/player1.png");
	player_textures.emplace_back();
	player_textures.back().loadFromFile("res/Sprites/player2.png");
	//Enemy Textures
	enemy_textures.emplace_back();
	enemy_textures.back().loadFromFile("res/Sprites/enemy1.png");
	enemy_textures.emplace_back();
	enemy_textures.back().loadFromFile("res/Sprites/enemy2.png");
	//Projectile Textures
	//Player
	projectile_textures.emplace_back();
	projectile_textures.back().loadFromFile("res/Sprites/bullet.png");
	//Enemy
	enemy_projectile_texture.emplace_back();
	enemy_projectile_texture.back().loadFromFile("res/Sprites/bullet.png");
	//Screen Effect
	broken_screen_texture.loadFromFile("res/Sprites/brokenscreen.png");
}

void Level1::setUpTimers()
{
	//Set up all of the main Timers and Spawners
	player_bullet_timer.setDuration(0.5f);
	enemy_spawner.setDuration(1.0f);

	
}

