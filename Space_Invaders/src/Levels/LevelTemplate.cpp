#include "LevelTemplate.h"
#include "MediaManager/SFXPlayer.h"


Level::Level() :Scene(),player_score(0),enemy_death_count(0),selected_slot(0)
{
	//set basic variables to their default state
	// Initialize key press states
	//Initialize the spawners
	
	spawners.emplace_back(new MemoryManagement::EnemySpawner<Enemy>(world_enemies));
	//Initialize collectors
	collectors.reserve(3);
	collectors.emplace_back(new MemoryManagement::Collector<Enemy>(world_enemies));
	collectors.emplace_back(new MemoryManagement::Collector<PlayerBullet>(player_bullets));
	collectors.emplace_back(new MemoryManagement::Collector<EnemyBullet>(world_enemy_bullets));
	key_u = false;
	key_d = false;
	key_l = false;
	key_r = false;
	key_s = false;
	player_max = false;

	//Debug
	xa = new Debug::XAxis(Scene::s_window, Scene::s_view, 100, Scene::s_view->getSize().x*4);
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
	if (key_u) { player->move(DIRECTIONS::UP); }
	else if (key_d) { player->move(DIRECTIONS::DOWN); }

	if (key_l) { player->move(DIRECTIONS::LEFT); }
	else if (key_r) { player->move(DIRECTIONS::RIGHT); }
	if (key_s) {
		if (player->canShoot()) {spawnPlayerBullet(); }
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
	
	player_bullets.emplace_back(new PlayerBullet(VectorMath::getAABBMidFront(player->getTopLeftPos(),
		player->getSize()), VectorMath::Vdirection::RIGHT));

	player_bullets.back()->setTexture(projectile_textures[selected_slot]);

	SFX::play(SFXlib::BulletShoot);
}

void Level::spawnEnemyBullet(Enemy* enemy)
{

	//call the function from the enemy that spawns the bullet
	world_enemy_bullets.emplace_back(enemy->spawnBullet());	
	SFX::play(SFXlib::BulletShoot);


}

