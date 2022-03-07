#include "BasicShooter.h"
#include "Algorithms/MathUtils.h"

#include <iostream>
//for debugging
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec);

ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name),
	  player(100, 0.5f, 100.0f),
	  starfield(m_window, m_view, 100),
	  player_bullet_timer(0.5f),
	  enemy_spawner(1.0f),
	  camera(m_window, m_view, &player, sf::Vector2f(100.0f, 0.0f))
{

	// Load Textures for Entities and Projectiles
	player_texture.loadFromFile("res/Sprites/player.png");
	enemy_texture.loadFromFile("res/Sprites/enemy.png");
	projectile_texture.loadFromFile("res/Sprites/bullet.png");
	// Setting the textures
	player.setTexture(player_texture);
	
	// Initialise keypress states
	key_u = false;
	key_d = false;
	key_l = false;
	key_r = false;
	key_s = false;
	// Create the initial Spawn of enemies
        // reserve space for our vectors
	world_enemies.reserve(50);
	world_enemy_bullets.reserve(80);
	player_bullets.reserve(80);
}

ShooterGame::~ShooterGame()
{
}

void ShooterGame::pollEvents()
{
	while (m_window->pollEvent(m_events))
	{
		
		// window events
		switch (m_events.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			if (m_events.key.code == sf::Keyboard::Escape){m_window->close();}
			//Player Input of key pressed
			playerInputState(STATES::PRESSED);
			break;
		case sf::Event::KeyReleased:
			//Player Input of key release
			playerInputState(STATES::RELEASED);
			break;
		// No more type of events
		default:
			break;
		}
	}
	// States Update
	if (key_u) {player.move(DIRECTIONS::UP);}
	else if (key_d) {player.move(DIRECTIONS::DOWN);}

	if (key_l) {player.move(DIRECTIONS::LEFT);}
	else if (key_r) {player.move(DIRECTIONS::RIGHT);}
	if (key_s) {
		if (player_bullet_timer.timeOut()) { SpawnPlayerBullet(); }
	}
}

void ShooterGame::update()
{
	// Get keypresses
	pollEvents();

	// Update Player physics
	player.updatePhysics();

	// Update spawners, enemies and bullets
	player_bullet_timer.start();
	//add enemy spawner
	enemy_spawner.start();
	if (enemy_spawner.timeOut()) {
		//calculate the position
		sf::Vector2f pos(m_view->getCenter().x + m_window->getSize().x / 2,
			m_view->getSize().y);
	
		SpawnEnemy(pos);
	}
	
	for (auto& playerbullet : player_bullets) {

		playerbullet->move();

	}
	for (auto& enemy : world_enemies) {
		enemy->move();
	}
	static float x = 0.0f;

	for (auto& enemy : world_enemies) {

		for (auto& playerbullet : player_bullets) {
			if (enemy->collidesWith(playerbullet)) {
				std::cout << "Collided\n";
			}
		}
		

	}

	// scroll camera
	camera.follow();

	
}

void ShooterGame::render()
{
	m_window->clear();
	
	// render background
	starfield.draw();
	
	// renders objects
	for (auto& enemy : world_enemies) {
		m_window->draw(enemy->getSprite());
	}
	for (auto& playerbullet : player_bullets) {
		m_window->draw(playerbullet->getSprite());
	}

	m_window->draw(player.getSprite());

	// displays objects on the screen
	m_window->display();
}



void ShooterGame::playerInputState(STATES state)
{
	switch (state)
	{
	case STATES::PRESSED:
		if (m_events.key.code == sf::Keyboard::A) { key_l = true; }
		else if (m_events.key.code == sf::Keyboard::D) { key_r = true; }
		if (m_events.key.code == sf::Keyboard::W) { key_u = true; }
		if (m_events.key.code == sf::Keyboard::S) { key_d = true; }
		if (m_events.key.code == sf::Keyboard::G) { key_s = true; }
		break;
	case STATES::RELEASED:
		if (m_events.key.code == sf::Keyboard::A) { key_l = false; }
		else if (m_events.key.code == sf::Keyboard::D) { key_r = false; }
		if (m_events.key.code == sf::Keyboard::W) { key_u = false; }
		if (m_events.key.code == sf::Keyboard::S) { key_d = false; }
		if (m_events.key.code == sf::Keyboard::G) { key_s = false; }
		break;
	default:
		break;
	}

}


void ShooterGame::SpawnEnemy(const sf::Vector2f& position )
{
	world_enemies.emplace_back(new Enemy(12,5,VectorMath::Vdirection::LEFT));
	world_enemies.back()->setTexture(enemy_texture);
	world_enemies.back()->setPosition(position);
}

void ShooterGame::SpawnPlayerBullet()
{
	
	player_bullets.emplace_back(new PlayerBullet(VectorMath::getAABBMidFront(player.getSprite().getPosition(),
		sf::Vector2f(player.getSprite().getTextureRect().width*player.getSprite().getScale().x, player.getSprite().getTextureRect().height) * player.getSprite().getScale().y),
		VectorMath::Vdirection::RIGHT));

	player_bullets.back()->setTexture(projectile_texture);
}

void ShooterGame::SpawnEnemyBullet()
{

}

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec) {
	stream << vec.x << "," << vec.y;
	return stream;
}
