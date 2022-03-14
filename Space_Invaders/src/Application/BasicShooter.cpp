#include "BasicShooter.h"
#include "Algorithms/MathUtils.h"

#include <iostream>
//for debugging
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec);
//Implemented by Daniel 02.27 11:00 AM
ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name),
	  player(100, 0.5f, 100.0f),
	  starfield(m_window, m_view, 25, 1.2f),
	  player_bullet_timer(0.5f),
	  enemy_spawner(1.0f),
	  camera(m_window, m_view, &player, sf::Vector2f(100.0f, 0.0f))
{
	//Implemented by Daniel 02.27 11:05 AM
	// Load Textures for Entities and Projectiles
	player_texture.loadFromFile("res/Sprites/player1.png");
	enemy_texture.loadFromFile("res/Sprites/enemy1.png");
	projectile_texture.loadFromFile("res/Sprites/bullet.png");
	broken_screen.loadFromFile("res/Sprites/brokenscreen.png");
	// Setting the textures
	player.setTexture(player_texture);
	
	//Added by Daniel and Luigi 02.28 2:00 pm
	// Initialize key press states
	key_u = false;
	key_d = false;
	key_l = false;
	key_r = false;
	key_s = false;

    // reserve space for our vectors
	world_enemies.reserve(50);
	world_enemy_bullets.reserve(80);
	player_bullets.reserve(80);

	//This is subject to change
	//Added by Daniel 03.07 11:00 PM
	rectangle.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	rectangle.setPosition(m_view->getCenter());
	rectangle.setFillColor(sf::Color(255,255,255,0));
	rectangle.setTexture(&broken_screen);
}

ShooterGame::~ShooterGame()
{
	//When the scenes are implemented here we eliminate any scene in the heap
}

//Added by Daniel 02.27 11:25 AM
void ShooterGame::pollEvents()
{
	while (m_window->pollEvent(m_events))
	{
		
		// window events
		//Added by Daniel 02.28 1:00 PM
		switch (m_events.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			if (m_events.key.code == sf::Keyboard::Escape){m_window->close();}
			//Player Input of key pressed
			//Added by Daniel 03.03 2:00 PM
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
	//Added by Daniel and Luigi 02.27 11:00 AM
	// States Update
	if (key_u) {player.move(DIRECTIONS::UP);}
	else if (key_d) {player.move(DIRECTIONS::DOWN);}

	if (key_l) {player.move(DIRECTIONS::LEFT);}
	else if (key_r) {player.move(DIRECTIONS::RIGHT);}
	if (key_s) {
		//Added by Daniel 03.05 2:00 PM
		if (player_bullet_timer.timeOut()) { SpawnPlayerBullet(); }
	}
}
//Added by Daniel 02.27 12:12 PM
void ShooterGame::update()
{
	// Get keypresses
	pollEvents();
	//Condition for the level-Subject to change
	if(player.getHP()>0){

	// Update Player physics
	//Added by Luigi set the time!!!!!!!!!!!!!!!!!!!!!!!!!
	player.updatePhysics();

	// Update spawners, enemies and bullets
	//Added by Daniel 03.07 12:00 AM
	player_bullet_timer.start();
	//add enemy spawner
	enemy_spawner.start();
	if (enemy_spawner.timeOut()) {
		//calculate the position
		sf::Vector2f pos(m_view->getCenter().x + m_view->getSize().x / 2,
			m_view->getSize().y);
	
		SpawnEnemy(pos);
	}
	
	//Entities and projectiles actions
	//Added by Daniel 03.05 5:00 PM
	for (auto& playerbullet : player_bullets) {

		playerbullet->move();

	}
	for (auto& enemy : world_enemies) {
		enemy->move();
		if (enemy->canShoot()) {
			SpawnEnemyBullet(VectorMath::getAABBMidBack(enemy->getTopLeftPos(),enemy->getSize()),VectorMath::Vdirection::LEFT);
			
		}
	}
	for (auto& enemybullet : world_enemy_bullets) {
		enemybullet->move();
	}

	//Collisions
	//Enemies
	//Added by Daniel 03.06 4:00 PM
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
		if (enemy->getHP()<=0) {
			is_dead = true;
			//delete the memory in the heap
			delete enemy;
		}

		return is_dead; }), world_enemies.end());
	//Player
	//Added by Daniel 03.06 4:15 PM
	world_enemy_bullets.erase(std::remove_if(world_enemy_bullets.begin(), world_enemy_bullets.end(), [&](EnemyBullet* enemy_bullet) {
		bool collided = player.collidesWith(enemy_bullet);
		if (collided) {
			player.hurt(enemy_bullet);
			std::cout << player.getHP() << "\n";
		}

		return collided; }),world_enemy_bullets.end());
	
	// scroll camera
	//Added by Luigi Set the time!!!!!!!!!!!!!!!!!!!!!!!!!
	camera.follow();

	}
	else {
		
		rectangle.setPosition(m_view->getCenter());
		rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	}
	
}
//Added by Daniel 02.27 12:30 PM
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
	for (auto& enemybullet : world_enemy_bullets) {
		m_window->draw(enemybullet->getSprite());
	}
	m_window->draw(player.getSprite());
	m_window->draw(rectangle);
	// displays objects on the screen
	m_window->display();
}


//Added by Daniel and Luigi 03.03 2:00 PM
void ShooterGame::playerInputState(STATES state)
{
	switch (state)
	{
	case STATES::PRESSED:
		if (m_events.key.code == sf::Keyboard::A) { key_l = true; }
		else if (m_events.key.code == sf::Keyboard::D) { key_r = true; }
		if (m_events.key.code == sf::Keyboard::W) { key_u = true; }
		else if (m_events.key.code == sf::Keyboard::S) { key_d = true; }

		if (m_events.key.code == sf::Keyboard::G) { key_s = true; }
		break;
	case STATES::RELEASED:
		if (m_events.key.code == sf::Keyboard::A) { key_l = false; }
		if (m_events.key.code == sf::Keyboard::D) { key_r = false; }
		if (m_events.key.code == sf::Keyboard::W) { key_u = false; }
		if (m_events.key.code == sf::Keyboard::S) { key_d = false; }
		
		if (m_events.key.code == sf::Keyboard::G) { key_s = false; }
		break;
	default:
		break;
	}

}
//Added by Daniel 03.05 3:00 PM
void ShooterGame::SpawnEnemy(const sf::Vector2f& position )
{
	world_enemies.emplace_back(new Enemy(12,5,VectorMath::Vdirection::LEFT));
	world_enemies.back()->setTexture(enemy_texture);
	world_enemies.back()->setPosition(position);
}
//Added by Daniel 03.05 2:32 PM
void ShooterGame::SpawnPlayerBullet()
{
	
	player_bullets.emplace_back(new PlayerBullet(VectorMath::getAABBMidFront(player.getTopLeftPos(),
		sf::Vector2f(player.getSize().x, player.getSize().y)),VectorMath::Vdirection::RIGHT));

	player_bullets.back()->setTexture(projectile_texture);
}
//Added by Daniel 03.05 3:15 PM
void ShooterGame::SpawnEnemyBullet(const sf::Vector2f& position, const sf::Vector2f dir)
{
	
	world_enemy_bullets.emplace_back(new EnemyBullet(position,dir));
	world_enemy_bullets.back()->setTexture(projectile_texture);
}
//Added by Daniel 03.02 5:00 PM
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec) {
	stream << vec.x << "," << vec.y;
	return stream;
}
