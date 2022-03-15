#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "SelectionMenu.h"
namespace SceneManagement {
	class Scene {
	public:
		static sf::RenderWindow* s_window;
		static sf::View* s_view;
		static sf::Event s_events;
	protected:
		bool m_finished;
		//sf::RenderWindow* m_window = nullptr;
	public:
		Scene():m_finished(false),m_return(false) {}
		virtual ~Scene() {}

		virtual void pollEvents() {}
		virtual void update(float delta_time) {}
		virtual void render() {}
		inline bool isSceneFinished() {return m_finished;}
		bool m_return;
		
	};
	class SceneMenu : public Scene {
	public:
		//The scene menu will take a pointer, and whatever that happens inside this class
		//will also modify the outside pointer
		SceneMenu(Scene*& currentScenePtr);
		void pollEvents()override;
		void update(float delta_time)override;
		void render()override;

		template <typename T>
		void registerScene(const std::string& name)
		{

			std::cout << "Registering Scene " << name << std::endl;
			m_Scenes.push_back(std::make_pair(name, []() {return new T(); }));

		}
		void setScene(const std::string& name);
		void nextScene();

		void handleSelection();
		void backToMenu();

	private:
		sf::RectangleShape m_background;
		sf::Texture m_texture;
		sf::Font title_font;
		sf::Text title;
		SelectionMenu selection;
		//contains a collection of scenes
		Scene*& m_CurrentScenePtr;//it will be turned into an alias of an outsider
		//scene ptr, thanks to this, we can access the methods in the scene
		std::vector < std::pair<std::string, std::function<Scene*()>>> m_Scenes;
		//we use std::function as a placeholder for the lambda
		//when we register, we register the name and its lambda
		std::pair<std::string, std::function<Scene* ()>>* m_sceneElement;
		
	};



}