#include "Scene.h"

namespace SceneManagement {

	//static variables initialization 
	sf::RenderWindow* Scene::s_window = nullptr;
	sf::View* Scene::s_view = nullptr;
	sf::Event Scene::s_events;

	SceneMenu::SceneMenu(Scene*& currentScenePtr)
		:Scene(),m_CurrentScenePtr(currentScenePtr)
	{
		m_CurrentScenePtr = this;
		m_texture.loadFromFile("res/Sprites/Cutscenes/menu_background.png");
		m_background.setSize(sf::Vector2f(Scene::s_window->getSize().x, Scene::s_window->getSize().y));
		m_background.setTexture(&m_texture);
		
		//m_background.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Scene::s_view->getSize().x, Scene::s_view->getSize().y)));
	}
	//Supposing we already registered Levels
	void SceneMenu::pollEvents()
	{

		while (Scene::s_window->pollEvent(Scene::s_events))
		{

			// window events
			//Added by Daniel 02.28 1:00 PM
			switch (s_events.type)
			{
			case sf::Event::Closed:
				s_window->close();
				break;
			case sf::Event::KeyPressed:
				if (s_events.key.code == sf::Keyboard::Escape) { s_window->close(); }
				else if(s_events.key.code==sf::Keyboard::X){
					//this means new game
					setScene(m_Scenes.front().first);
				}
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
	}

	void SceneMenu::render()
	{
		Scene::s_window->draw(m_background);
	}


	//template<typename T>
	//void SceneManagement::SceneMenu::registerScene(const std::string& name)
	//{
	//	
	//	std::cout << "Registering Scene " << name << std::endl;
	//	m_Scenes.push_back(std::make_pair(name, [](){return new T(); }));
	//	
	//}


	//only call this function at the beginning
	void SceneMenu::setScene(const std::string& name)
	{
		//if the name of the scene we are looking for has been registered
		//then the SceneMenu is going to create that scene for us
		//and the pointer in the game will be updated.
		for (auto& scene : m_Scenes) {
			if (name == scene.first.c_str()) {
				//instantiates the scene
				if (m_CurrentScenePtr && m_CurrentScenePtr != this) {
					//this is just to avoid deleting the menu
					delete m_CurrentScenePtr;
				}

			}
			m_CurrentScenePtr = scene.second();
			m_sceneElement = &scene;

			break;

		}
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

	

	
