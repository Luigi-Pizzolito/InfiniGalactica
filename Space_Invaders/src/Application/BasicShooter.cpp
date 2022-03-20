#include "BasicShooter.h"
#include "Algorithms/MathUtils.h"
#include "Scenes/BasicNovel.h"
#include "Scenes/Credits.h"
#include "MediaManager/SFXPlayer.h"
#include <iostream>

#include "Levels/ShooterLevel.h"

ShooterGame::ShooterGame(const sf::Vector2i &screen_dimensions, const char *app_name)
	// Initializer List
	: Application(screen_dimensions, app_name)
	

{	//set the window
	SceneManagement::Scene::s_window = m_window;
	//set the view
	SceneManagement::Scene::s_view = m_view;
	m_currentScene = nullptr;
	//Here the current scene is the main menu
	m_menu = new SceneManagement::SceneMenu(m_currentScene);
	SceneManagement::Scene::s_main_menu = m_menu;
	//In order to let any Scene/Level access events we

	//Register Levels using the menu/SceneManager
	// m_menu->registerScene<NovelGame>(std::string("Novel Test"));
	m_menu->registerScene(std::string("credits"));
	// m_menu->registerScene<Level1>(std::string("Level1"));
	// m_menu->registerScenePassJSON<ShooterLevel>(std::string("level1"));
	m_menu->registerScene(std::string("level1"));
	//Load SFX library
	SFX::loadLib();
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

		if (m_currentScene->isSceneFinished()) {
			m_menu->nextScene();
		}

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
