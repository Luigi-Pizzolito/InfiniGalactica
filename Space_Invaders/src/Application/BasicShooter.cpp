#include "BasicShooter.h"
#include "Algorithms/MathUtils.h"
#include "MediaManager/SFXPlayer.h"
#include <iostream>

// #include <filesystem>
#include <json.hpp>
using json = nlohmann::json;
#include <fstream>

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
	// m_menu->registerScene(std::string("credits"));
	// m_menu->registerScene<Level1>(std::string("Level1"));
	// m_menu->registerScenePassJSON<ShooterLevel>(std::string("level1"));
	// m_menu->registerScene(std::string("novel1"));
	// m_menu->registerScene(std::string("level1"));
	// m_menu->registerScene(std::string("level1"));
	// for (auto& dirEntry: std::filesystem::recursive_directory_iterator("res/Scenes")) {
	// 	if (!dirEntry.is_regular_file()) continue; //skip directories, symlinks, etc
	// 	std::filesystem::path file = dirEntry.path();
	// 	std::string filename_noext = std::string(file.filename().string());
	// 	filename_noext.replace(filename_noext.find(std::string(file.extension().string())),std::string(file.extension().string()).length(),std::string(""));

	// 	if (std::string(file.extension().string()) == ".json") {
	// 		// std::cout << "Scene Manager: Found file: " << filename_noext << file.extension().string() << "\n";
	// 		m_menu->registerScene(filename_noext);
	// 	}

	// }
	std::ifstream ifs(std::string("res/Scenes/load_order.json"));
	json ld = json::parse(ifs);
	for(auto& file : ld) {
		m_menu->registerScene(file);
	}

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
		if (m_currentScene->isSceneFinished()) {
			m_menu->nextScene();
		} else {
			m_currentScene->update(60.0f);
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
