#include "LevelTemplate.h"
#include "MediaManager/SFXPlayer.h"
#include "GameItems/GameItem.h"

Level::Level() :Scene(),player_score(0),enemy_death_count(0),selected_slot(0),
world_position(sf::Vector2f(0.0f,0.0f)),total_length(sf::Vector2f(0.0f, 0.0f))
{
	//set basic variables to their default state
	// Initialize key press states
	//Initialize the spawners
	
	spawners.emplace_back(new MemoryManagement::EnemySpawner<Enemy>(world_enemies,world_position,total_length));
	spawners.emplace_back(new MemoryManagement::EnemySpawner<Furtive>(world_enemies, world_position, total_length));
	spawners.emplace_back(new MemoryManagement::EnemySpawner<Attacker>(world_enemies, world_position, total_length));

	item_spawners.emplace_back(new MemoryManagement::BaseItemSpawner(world_items));
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
	
	player_bullets.emplace_back(new PlayerBullet(player->getBulletDamage(),player->getBulletSpeed(),VectorMath::getAABBMidFront(player->getCenterPos(),
		player->getSize()), VectorMath::Vdirection::RIGHT));

	player_bullets.back()->setTexture(projectile_textures[selected_slot], sf::Vector2f(0.5f, 0.3f));

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

