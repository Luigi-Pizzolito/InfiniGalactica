#include "BasicShooter.h"
#include "Algorithms/MathUtils.h"
#include "Levels/Level_1.h"
#include <iostream>
//for debugging
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec);
//Implemented by Daniel 02.27 11:00 AM
ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name)
	  //player(100, 0.5f, 100.0f),
	  //starfield(m_window, m_view, 25, 1.2f),
	  //player_bullet_timer(0.5f),
	  //enemy_spawner(1.0f),
	  //camera(m_window, m_view, &player, sf::Vector2f(100.0f, 0.0f))


{
	SceneManagement::Scene::s_window = m_window;
	//set the view
	SceneManagement::Scene::s_view = m_view;
	m_currentScene = nullptr;
	m_menu = new SceneManagement::SceneMenu(m_currentScene);
	//In order to let any Scene/Level access events we
	//set the window


	//Register Levels using the menu/SceneManager
	m_menu->registerScene<Level1>(std::string("Level1"));
}

//When closing the application
ShooterGame::~ShooterGame()
{
	//When the scenes are implemented here we eliminate any scene in the heap
	if (m_currentScene) {
		if (m_currentScene == m_menu) {
			m_menu = nullptr;
		}
		delete m_currentScene;
	}
	//deletes the menu 
	if (m_menu) {
		delete m_menu;
	}
}


//Added by Daniel 02.27 12:12 PM
void ShooterGame::update()//reimplement for every level
{

	//change this deltatime later
	if (m_currentScene) {
		m_currentScene->update(60.0f);

	}

		

	//add conditions to change the current scene
	//if currentscene.finished(){scenemenu.nextscene}


}
//Added by Daniel 02.27 12:30 PM
void ShooterGame::render()//reimplement for every level
{
	//can keep the clear function here
	m_window->clear();
	if (m_currentScene) {
		m_currentScene->render();

	}
	m_window->display();
}



//Added by Daniel 03.02 5:00 PM
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec) {
	stream << vec.x << "," << vec.y;
	return stream;
}
