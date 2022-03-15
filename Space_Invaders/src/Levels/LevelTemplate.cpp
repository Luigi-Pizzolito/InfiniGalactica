#include "LevelTemplate.h"



Level::Level() :Scene(),player_score(0),enemy_death_count(0),selected_slot(0)
{
	//set basic variables to their default state
	// Initialize key press states
	key_u = false;
	key_d = false;
	key_l = false;
	key_r = false;
	key_s = false;
	player_max = false;

}



Level::~Level()
{

}
void Level::pollEvents()
{

	while (Scene::s_window->pollEvent(Scene::s_events))
	{

		// window events
		switch (Scene::s_events.type)
		{
		case sf::Event::Closed:
			Scene::s_window->close();
			break;
		case sf::Event::KeyPressed:
			playerInputStates(STATES::PRESSED);
			if (Scene::s_events.key.code == sf::Keyboard::Q) {
				switchSlot();
			}
			if (Scene::s_events.key.code == sf::Keyboard::Escape) {
				Scene::s_window->close();
			}
			break;
		case sf::Event::KeyReleased:
			//Player Input of key release
			playerInputStates(STATES::RELEASED);
			break;
			// No more type of events
		default:
			break;
		}
	}
	// States Update
	if (key_u) { player->move(DIRECTIONS::UP); }
	else if (key_d) { player->move(DIRECTIONS::DOWN); }

	if (key_l) { player->move(DIRECTIONS::LEFT); }
	else if (key_r) { player->move(DIRECTIONS::RIGHT); }
	if (key_s) {
		if (player_bullet_timer.timeOut()) {spawnPlayerBullet(); }
	}
}

void Level::playerInputStates(STATES state)
{
	//sets the states of the keys that require continuous input
	switch (state)
	{
	case STATES::PRESSED:
		if (Scene::s_events.key.code == sf::Keyboard::A) { key_l = true; }
		else if (Scene::s_events.key.code == sf::Keyboard::D) { key_r = true; }
		if (Scene::s_events.key.code == sf::Keyboard::W) { key_u = true; }
		else if (Scene::s_events.key.code == sf::Keyboard::S) { key_d = true; }

		if (Scene::s_events.key.code == sf::Keyboard::G) { key_s = true; }
		break;
	case STATES::RELEASED:
		if (Scene::s_events.key.code == sf::Keyboard::A) { key_l = false; }
		if (Scene::s_events.key.code == sf::Keyboard::D) { key_r = false; }
		if (Scene::s_events.key.code == sf::Keyboard::W) { key_u = false; }
		if (Scene::s_events.key.code == sf::Keyboard::S) { key_d = false; }

		if (Scene::s_events.key.code == sf::Keyboard::G) { key_s = false; }
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

void Level::spawnEnemy(const sf::Vector2f& position)
{
	//health,speed,direction
	int range = 1 - 0 + 1;
	int num = rand() % range + 0;
	world_enemies.emplace_back(new Enemy(12, 5, VectorMath::Vdirection::LEFT));
	world_enemies.back()->setTexture(enemy_textures[num]);
	world_enemies.back()->setPosition(position);
}

void Level::spawnPlayerBullet()
{
	
	player_bullets.emplace_back(new PlayerBullet(VectorMath::getAABBMidFront(player->getTopLeftPos(),
		player->getSize()), VectorMath::Vdirection::RIGHT));

	player_bullets.back()->setTexture(projectile_textures[selected_slot]);
}

void Level::spawnEnemyBullet(const sf::Texture& texture,const sf::Vector2f& position, const sf::Vector2f dir)
{

	world_enemy_bullets.emplace_back(new EnemyBullet(position, dir));
	world_enemy_bullets.back()->setTexture(texture);

}


