#include "Scene.h"
#include <iostream>
namespace SceneManagement {

	//static variables initialization 
	sf::RenderWindow* Scene::s_window = nullptr;
	sf::View* Scene::s_view = nullptr;
	sf::Event Scene::s_events;



	SceneMenu::SceneMenu(Scene*& currentScenePtr)
		:Scene(),m_CurrentScenePtr(currentScenePtr),
		 selection(Scene::s_window, Scene::s_view)
	{
		m_CurrentScenePtr = this;
		m_texture.loadFromFile("res/Sprites/Cutscenes/menu_background.png");
		m_background.setSize(sf::Vector2f(Scene::s_window->getSize().x, Scene::s_window->getSize().y));
		m_background.setTexture(&m_texture);
		
		//m_background.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Scene::s_view->getSize().x, Scene::s_view->getSize().y)));

		title.setString("InfiniGalactica");
		title_font.loadFromFile("res/Novel/Linebeam.ttf");
		title.setFont(title_font);
		title.setCharacterSize(150);
		title.setOrigin(sf::Vector2f((-Scene::s_view->getSize().x/2)+(title.getGlobalBounds().width/2), -Scene::s_view->getSize().y/5));
		title.setFillColor(sf::Color::White);

		selection.addOptions(std::string("Continue"));
		selection.addOptions(std::vector<std::string> {"New Game", "Endless Mode", "Options", "Credits", "Exit"});
	}

	void SceneMenu::handleSelection() {
		if (selection.selected) {
			std::string selec = selection.selection();
			std::cout << "Selected " << selec << "\n";

			// handle selection choice
			// for first layer menu
			if (selec == "Exit") {
				s_window->close();
			} else
			if (selec == "Continue") {
				setScene(std::string("Novel Test"));
			} else
			if (selec == "New Game") {
				setScene(std::string("Level1"));
			} else
			if (selec == "Endless Mode") {

			} else
			if (selec == "Options") {

			} else
			if (selec == "Credits") {

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
				// if (s_events.key.code == sf::Keyboard::Escape) { s_window->close(); }
				selection.handleInput(s_events);
				// if(s_events.key.code==sf::Keyboard::X){
				// 	//this means new game
				// 	// setScene(m_Scenes.front().first);
				// 	setScene(std::string("Level1"));
				// } else if(s_events.key.code==sf::Keyboard::Z){
				// 	//this means novel test
				// 	setScene(std::string("Novel Test"));
				// }
				// // !!! BUG: set scene does not block input handling fast enough, if X and Z are pressed at the same time then both scenes are initialised in memory.
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
	}

	void SceneMenu::render()
	{
		// Scene::s_window->draw(m_background);
		selection.draw();
		Scene::s_window->draw(title);
	}


	void SceneMenu::setScene(const std::string& name)
	{
		//if the name of the scene we are looking for has been registered
		//then the SceneMenu is going to create that scene for us
		//and the pointer in the game will be updated.
		for (auto& scene : m_Scenes) {
			std::cout << "scene is: \"" << scene.first.c_str() << "\" search pattern is \"" + name + "\"\n";
			if (name == scene.first.c_str()) {
				//instantiates the scene
				if (m_CurrentScenePtr && m_CurrentScenePtr != this) {
					//this is just to avoid deleting the menu
					delete m_CurrentScenePtr;
				}

				m_CurrentScenePtr = scene.second();
				m_sceneElement = &scene;
				break;
			}

		}
	}


	void SceneMenu::backToMenu() {
		m_CurrentScenePtr = this;
		m_sceneElement = nullptr;		// scene element is reset here as there is no scene element for menu
										// be sure to set this when next switching to a scene
	}

	//this function helps to the transition of levels
	void SceneMenu::nextScene()
	{
		if (m_CurrentScenePtr && m_CurrentScenePtr != this) {
			//this is just to avoid deleting the menu
			delete m_CurrentScenePtr;
		}
		//for extra safety, if someone for some reason sets a scene that is not the 1st one as
		//the 1st scene
		if (m_sceneElement != &m_Scenes.back()) {
			m_sceneElement++;//move to the next pair
			m_CurrentScenePtr = m_sceneElement->second();

		}
		else {
			//this means that the last scene(credits has finished)
			delete m_CurrentScenePtr;
			//go back to the menu
			m_CurrentScenePtr = this;
		}
		

	}



}

	

	
