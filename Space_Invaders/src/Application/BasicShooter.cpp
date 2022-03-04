#include "BasicShooter.h"

#include "CameraFollowScroll.h"

ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name),
	  player(100, 25, 500.0f),
	  starfield(m_window, &player.getSprite(), 500)
{

	// Load Textures for Entities and Projectiles
	player_texture.loadFromFile("res/Sprites/player.png");
	enemy_texture.loadFromFile("res/Sprites/enemy.png");
	projectile_texture.loadFromFile("res/Sprites/bullet.png");
	// Setting the textures
	player.setTexture(player_texture);
	#ifdef __APPLE__
	key_u = false;
	key_d = false;
	key_l = false;
	key_r = false;
	#endif
	// Create the initial Spawn of enemies
}

ShooterGame::~ShooterGame()
{
}

void ShooterGame::pollEvents()
{
	#ifdef __APPLE__
	if (key_u) {player.move(DIRECTIONS::UP);}
	else if (key_d) {player.move(DIRECTIONS::DOWN);}
	if (key_l) {player.move(DIRECTIONS::LEFT);}
	else if (key_r) {player.move(DIRECTIONS::RIGHT);}
	#endif
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
			// This will change later
			#ifdef __APPLE__
			if (m_events.key.code == sf::Keyboard::A){key_l = true;}
			else if (m_events.key.code == sf::Keyboard::D){key_r = true;}
			if (m_events.key.code == sf::Keyboard::W){key_u = true;}
			if (m_events.key.code == sf::Keyboard::S){key_d = true;}
			#endif
			#ifndef __APPLE__
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {player.move(DIRECTIONS::LEFT);}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {player.move(DIRECTIONS::RIGHT);}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {player.move(DIRECTIONS::UP);}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {player.move(DIRECTIONS::DOWN);}
			#endif
			break;
		#ifdef __APPLE__
		case sf::Event::KeyReleased:
			if (m_events.key.code == sf::Keyboard::A){key_l = false;}
			else if (m_events.key.code == sf::Keyboard::D){key_r = false;}
			if (m_events.key.code == sf::Keyboard::W){key_u = false;}
			if (m_events.key.code == sf::Keyboard::S){key_d = false;}
			break;
		#endif
		// No more type of events
		default:
			// This will change later
			break;
		}
	}
}

void ShooterGame::update()
{
	pollEvents();
	player.updatePhysics();		// Also need to update the player physics every frame
}

void ShooterGame::render()
{
	m_window->clear();
	// scroll camera
	CameraFollowHorzScroll(m_window, m_view, &player.getSprite());
	// render background
	starfield.draw();
	
	// renders objects
	m_window->draw(player.getSprite());
	// displays objects on the screen
	m_window->display();
}