#include "Scene.h"
#include <iostream>
#include <json.hpp>
using json = nlohmann::json;
#include <fstream>

#include "Levels/ShooterLevel.h"
#include "Scenes/Credits.h"
#include "Scenes/NovelScene.h"
namespace SceneManagement {

	//static variables initialization 
	sf::RenderWindow* Scene::s_window = nullptr;
	sf::View* Scene::s_view = nullptr;
	sf::Event Scene::s_events;
	SceneMenu* Scene::s_main_menu = nullptr;


	SceneMenu::SceneMenu(Scene*& currentScenePtr)
		:Scene(),m_CurrentScenePtr(currentScenePtr),
		 selection(Scene::s_window, Scene::s_view),
		 rstarfield(Scene::s_window,Scene::s_view,250,10.0f),
		 music("song3", true)
	{
		m_CurrentScenePtr = this;
		// m_texture.loadFromFile("res/Sprites/Cutscenes/menu_background.png");
		// m_background.setSize(sf::Vector2f(Scene::s_window->getSize().x, Scene::s_window->getSize().y));
		// m_background.setTexture(&m_texture);
		// Music pos update for looping
		music.update(0.6f);
		title.setString("InfiniGalactica");
		title_font.loadFromFile("res/Novel/Linebeam.ttf");
		title.setFont(title_font);
		float c_siz = 150.0f;
		title.setCharacterSize(c_siz);
		// get the largest size that will fit in bounds with padding
		while (title.getGlobalBounds().width > Scene::s_view->getSize().x-Scene::s_view->getSize().x/8) {
			c_siz -=5;
			title.setCharacterSize(c_siz);
		}
		
		title.setOrigin(sf::Vector2f((-Scene::s_view->getSize().x/2)+(title.getGlobalBounds().width/2), -Scene::s_view->getSize().y/5));
		title.setFillColor(sf::Color::White);
		//todo: use another while loop to get vertical spacing bounds for selection on smaller screens
		selection.addOptions(std::string("Continue"));
		selection.addOptions(std::vector<std::string> {"New Game", "Endless Mode", "Credits", "Exit"});

		f_in = new Composit::Fade(s_window, s_view, false, 2);
		f_in->trigger();
	}

	void SceneMenu::handleSelection() {
		if (selection.selected) {
			std::string selec = selection.selection();
			std::cout << "Scene Menu: Selected " << selec << "\n";

			// handle selection choice
			// for first layer menu
			if (selec == "Exit") {
				s_window->close();
			} else
			if (selec == "Continue") {
				setScene(std::string("novel1"));
			} else
			if (selec == "New Game") {
				setScene(std::string("level1"));
			} else
			if (selec == "Endless Mode") {

			} else
			if (selec == "Options") {

			} else
			if (selec == "Credits") {
				setScene(std::string("credits"));
			}


			selection.selected = false;
		}
	}



	//Supposing we already registered Levels
	void SceneMenu::pollEvents()
	{

		while (Scene::s_window->pollEvent(Scene::s_events))
		{

			// window events
			switch (s_events.type)
			{
			case sf::Event::Closed:
				s_window->close();
				break;
			case sf::Event::KeyPressed:
				if (s_events.key.code == sf::Keyboard::Escape) { 
					if ( selection.selection_i != selection.lastOpt()) {
						selection.selection_i = selection.lastOpt();
					} else {
						selection.selected = true;
					}
				}

				selection.handleInput(s_events);
				break;

				// No more type of events
			default:
				break;
			}
		}
	}

	void SceneMenu::update(float delta_time)
	{
		pollEvents();
		handleSelection();
		if (music.position() == 0) {
			music.play();
		}
	}

	void SceneMenu::render()
	{
		// Scene::s_window->draw(m_background);
		rstarfield.draw();
		selection.draw();
		Scene::s_window->draw(title);
		f_in->draw();
	}


	void SceneMenu::registerScene(const std::string& json_file) {
		//wrapper for loading scene of different base C++ types based on sceneType json key
		std::ifstream ifs(std::string("res/Scenes/")+json_file+std::string(".json"));
		json cfg = json::parse(ifs);
		if (cfg["sceneType"] == "shooterLevel") {
			registerScenePassJSON<ShooterLevel>(json_file);
		} else
		if (cfg["sceneType"] == "novelLevel") {
			registerScenePassJSON<NovelLevel>(json_file);
		} else
		if (cfg["sceneType"] == "credits") {
			registerScenePassJSON<Credits>(json_file);
		}
	}

	

	void SceneMenu::setScene(const std::string& name)
	{
		//if the name of the scene we are looking for has been registered
		//then the SceneMenu is going to create that scene for us
		//and the pointer in the game will be updated.
		for (auto& scene : m_Scenes) {
			// std::cout << "scene is: \"" << scene.first.c_str() << "\" search pattern is \"" + name + "\"\n";
			if (name == scene.first.c_str()) {
				//instantiates the scene
				if (m_CurrentScenePtr && m_CurrentScenePtr != this) {
					//this is just to avoid deleting the menu
					delete m_CurrentScenePtr;
				}

				std::ifstream ifs(std::string("res/Scenes/")+scene.first+std::string(".json"));
				json cfg = json::parse(ifs);
				m_CurrentScenePtr = scene.second(cfg);
				m_sceneElement = &scene;

				if (strcmp(name.c_str(), "credits") != 0) {
					// std::cout << "pausing music, not going to credits\n";
					Scene::s_main_menu->music.pause();
				}
				break;
			}

		}
	}

	//this function helps to the transition of levels
	void SceneMenu::nextScene()
	{
		if (m_CurrentScenePtr && m_CurrentScenePtr != this) {
			//this is just to avoid deleting the menu
			delete m_CurrentScenePtr;
			m_CurrentScenePtr = nullptr;
		}
		//for extra safety, if someone for some reason sets a scene that is not the 1st one as
		//the 1st scene
		if (m_sceneElement != &m_Scenes.back()) {
			m_sceneElement++;//move to the next pair
			std::ifstream ifs(std::string("res/Scenes/")+m_sceneElement->first+std::string(".json"));
			json cfg = json::parse(ifs);
			m_CurrentScenePtr = m_sceneElement->second(cfg);

		}
		else {
			//this means that the last scene(credits has finished)
			//delete m_CurrentScenePtr;
			////go back to the menu
			//m_CurrentScenePtr = this;
			goBackToMainMenu();
		}
		

	}

	void goBackToMainMenu()
	{
		std::cout << "Scene Menu: going back to main menu from : " << Scene::s_main_menu->m_sceneElement->first.c_str() << "\n";
		if (Scene::s_main_menu->m_CurrentScenePtr&& (Scene::s_main_menu->m_CurrentScenePtr!= Scene::s_main_menu)) {
			//delete the current scene
			delete Scene::s_main_menu->m_CurrentScenePtr;
		}
		if (Scene::s_main_menu->m_sceneElement->first != std::string("credits")) {
			// std::cout << "resuming music, came from not credits\n";
			Scene::s_main_menu->music.play();
		}
		//set the scene pointer to the first scene(not needed but elegant)
		Scene::s_main_menu->m_sceneElement = Scene::s_main_menu->m_Scenes.data();
		Scene::s_main_menu->m_CurrentScenePtr = Scene::s_main_menu;
		Scene::s_view->setCenter(Scene::s_view->getSize().x/2, Scene::s_view->getSize().y / 2); //compensate for setCenter instead of setOffset func.
		Scene::s_window->setView(*Scene::s_view);

		std::cout << "Scene Menu: Current scene is: " << Scene::s_main_menu->m_sceneElement->first.c_str() << "\n"; 
		
	}


}

	

	
