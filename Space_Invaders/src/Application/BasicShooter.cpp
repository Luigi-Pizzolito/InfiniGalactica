#include "BasicShooter.h"
#include "Algorithms/MathUtils.h"
#include "Levels/Level_1.h"
#include "Scenes/BasicNovel.h"
#include <iostream>

ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name)
{
	SceneManagement::Scene::s_window = m_window;
	//set the view
	SceneManagement::Scene::s_view = m_view;
	m_currentScene = nullptr;
	m_menu = new SceneManagement::SceneMenu(m_currentScene);
	//In order to let any Scene/Level access events we
	//set the window


	//Register Levels using the menu/SceneManager
	m_menu->registerScene<NovelGame>(std::string("Novel Test"));
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


void ShooterGame::update()//reimplement for every level
{

	//change this deltatime later
	if (m_currentScene) {
		m_currentScene->update(60.0f);

	}

		
	//todo: add a method so that scenes can call when they have finished for scene manager to advance to the next scene
	//add conditions to change the current scene
	//if currentscene.finished(){scenemenu.nextscene}

	if (m_currentScene->m_return) {
		m_currentScene->m_return = false;
		m_menu->backToMenu();
		// m_currentScene = nullptr;
		m_currentScene = nullptr;
		//! this causes seg fault
	}

}
void ShooterGame::render()//reimplement for every level
{
	//can keep the clear function here
	m_window->clear();
	if (m_currentScene) {
		m_currentScene->render();

	}
	m_window->display();
}