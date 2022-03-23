#include "LevelTemplate.h"
#include "MediaManager/SFXPlayer.h"
#include "GameItems/GameItem.h"

Level::Level() :Scene(),player_score(0),enemy_death_count(0),selected_slot(0),
world_position(sf::Vector2f(0.0f,0.0f)),total_length(sf::Vector2f(0.0f, 0.0f))
{
	//set basic variables to their default state
	// Initialize key press states

	//Initialize collectors
	collectors.reserve(4);
	collectors.emplace_back(new MemoryManagement::Collector<Enemy>(world_enemies));
	collectors.emplace_back(new MemoryManagement::Collector<PlayerBullet>(player_bullets));
	collectors.emplace_back(new MemoryManagement::Collector<EnemyBullet>(world_enemy_bullets));
	collectors.emplace_back(new MemoryManagement::Collector<GameItem>(world_items));
	key_u = false;
	key_d = false;
	key_l = false;
	key_r = false;
	key_s = false;
	player_max = false;
	f_in = new Composit::Fade(s_window, s_view, false, 4);
	f_in->trigger();
	

	//Debug
	xa = new Debug::XAxis(Scene::s_window, Scene::s_view, &total_length);
}



Level::~Level()
{
	//Delete the collectors and spawners
	delete f_in;
}
void Level::pollEvents()
{

	while (Scene::s_window->pollEvent(Scene::s_events))
	{

		// window events
		switch (Scene::s_events.type)
		{
		case sf::Event::Closed:
			// Scene::s_window->close();
			pSc->pre();
			paused = true;
			break;
		case sf::Event::KeyPressed:
			if (!paused) {
				playerInputStates(STATES::PRESSED);
				if (Scene::s_events.key.code == sf::Keyboard::Q) {
					switchSlot();
				}
				if (Scene::s_events.key.code == sf::Keyboard::Escape) {
					pSc->pre();
					paused = true;
				}
			} else {
				pSc->handleInput(s_events);
			}
			break;
		case sf::Event::KeyReleased:
			//Player Input of key release
			playerInputStates(STATES::RELEASED);
			break;

		case sf::Event::MouseButtonPressed:
			key_s = true;
			break;
		case sf::Event::MouseButtonReleased:
			key_s = false;
			break;

			// No more type of events
		default:
			break;
		}
	}
	// States Update
	if (!paused) {
		if (key_u) { player->move(DIRECTIONS::UP); }
		else if (key_d) { player->move(DIRECTIONS::DOWN); }

		if (key_l) { player->move(DIRECTIONS::LEFT); }
		else if (key_r) { player->move(DIRECTIONS::RIGHT); }
		if (key_s) {
			if (player->canShoot()) {spawnPlayerBullet(); }
		}
	}
}

void Level::playerInputStates(STATES state)
{
	//sets the states of the keys that require continuous input
	switch (state)
	{
	case STATES::PRESSED:
		if 		(Scene::s_events.key.code == sf::Keyboard::A || Scene::s_events.key.code == sf::Keyboard::Left) { key_l = true; }
		else if (Scene::s_events.key.code == sf::Keyboard::D || Scene::s_events.key.code == sf::Keyboard::Right) { key_r = true; }
		if 		(Scene::s_events.key.code == sf::Keyboard::W || Scene::s_events.key.code == sf::Keyboard::Up) { key_u = true; }
		else if (Scene::s_events.key.code == sf::Keyboard::S || Scene::s_events.key.code == sf::Keyboard::Down) { key_d = true; }

		if (Scene::s_events.key.code == sf::Keyboard::G || Scene::s_events.key.code == sf::Keyboard::Space || Scene::s_events.key.code == sf::Keyboard::M) { key_s = true; }
		break;
	case STATES::RELEASED:
		if (Scene::s_events.key.code == sf::Keyboard::A || Scene::s_events.key.code == sf::Keyboard::Left) { key_l = false; }
		if (Scene::s_events.key.code == sf::Keyboard::D || Scene::s_events.key.code == sf::Keyboard::Right) { key_r = false; }
		if (Scene::s_events.key.code == sf::Keyboard::W || Scene::s_events.key.code == sf::Keyboard::Up) { key_u = false; }
		if (Scene::s_events.key.code == sf::Keyboard::S || Scene::s_events.key.code == sf::Keyboard::Down) { key_d = false; }

		if (Scene::s_events.key.code == sf::Keyboard::G || Scene::s_events.key.code == sf::Keyboard::Space || Scene::s_events.key.code == sf::Keyboard::M) { key_s = false; }
		break;
	default:
		break;
	}
}

void Level::switchSlot()
{
	//Basically switch to the next weapon available
	//indices start at 0 and end at size-1
	if (selected_slot <player_bullets.size()) {
		selected_slot++;
	}
	else {
		selected_slot = 0;
	}
}


void Level::spawnPlayerBullet()
{
	
	player_bullets.emplace_back(new PlayerBullet(player->getBulletDamage(),player->getBulletSpeed(),VectorMath::getAABBMidFront(player->getCenterPos(),
		player->getSize()), VectorMath::Vdirection::RIGHT));

	player_bullets.back()->setTexture(projectile_textures[selected_slot], sf::Vector2f(0.3f, 0.3f));

	SFX::play(SFXlib::BulletShoot);
}

void Level::spawnEnemyBullet(Enemy* enemy)
{

	//call the function from the enemy that spawns the bullet
	for (int i = 0; i < enemy->getBulletsCount(); i++) {
	
		world_enemy_bullets.emplace_back(enemy->spawnBullet(i));
		SFX::play(SFXlib::BulletShoot);
	}
	
	


}

void Level::updateWorldPosition()
{
	// to convert to"meters" divide by 100
	sf::Vector2f viewport_topleftpos= VectorMath::getViewPortTopLeftPos() / 100.0f;
	if (viewport_topleftpos.x > 0) {
		world_position = viewport_topleftpos;
	}
	

}

void Level::updateEntityCollisions()
{
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

void Level::updateEntities()
{
	// Update Player physics
	player->updatePhysics();
	updateWorldPosition();
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

}

