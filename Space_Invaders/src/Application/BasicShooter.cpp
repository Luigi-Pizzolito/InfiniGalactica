#include "BasicShooter.h"

// Physics parameters also needed for camera follow calculations

ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name),
	  player(100, 0.5f, 100.0f),
	  starfield(m_window, m_view, 100),
	  camera(m_window, m_view, &player, sf::Vector2f(100.0f, 0.0f))
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
	#ifdef __APPLE__
	if (key_u) {player.move(DIRECTIONS::UP);}
	else if (key_d) {player.move(DIRECTIONS::DOWN);}
	if (key_l) {player.move(DIRECTIONS::LEFT);}
	else if (key_r) {player.move(DIRECTIONS::RIGHT);}
	#endif
}

void ShooterGame::update()
{
	pollEvents();

	player.updatePhysics();
	// scroll camera
	camera.follow();

	// float border_width = 5.0f;
	// sf::FloatRect player_bounds = player.getSprite().getGlobalBounds();
    // sf::FloatRect view_bounds( m_view->getCenter()-(m_view->getSize()/2.0f) + sf::Vector2f(border_width, border_width) , m_view->getSize() + sf::Vector2f(-border_width, -border_width) );

	// if (view_bounds.contains(sf::Vector2f(player_bounds.top,player_bounds.left)) &&
	// 	view_bounds.contains(sf::Vector2f(player_bounds.top,player_bounds.left+player_bounds.width)) &&
	// 	view_bounds.contains(sf::Vector2f(player_bounds.top-player_bounds.height,player_bounds.left)) &&
	// 	view_bounds.contains(sf::Vector2f(player_bounds.top-player_bounds.height,player_bounds.left+player_bounds.width))
	//  ) {} else {std::cout<<"no physics\n";}		// Also need to update the player physics every frame

	
}

void ShooterGame::render()
{
	m_window->clear();
	
	// render background
	starfield.draw();
	
	// renders objects
	m_window->draw(player.getSprite());

	// displays objects on the screen
	m_window->display();
}