#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <json.hpp>
using json = nlohmann::json;

#include "SceneManager/SceneUtils/SelectionMenu.h"
#include "MediaManager/MusicPlayer.h"
#include "Algorithms/StarField.h"

#include "SceneManager/SceneUtils/Composit.h"

namespace SceneManagement {

	class SceneMenu;
	class Scene {
	public:
		static sf::RenderWindow* s_window;
		static sf::View* s_view;
		static sf::Event s_events;
		static SceneMenu* s_main_menu;

	protected:
		bool m_finished;
		//sf::RenderWindow* m_window = nullptr;
	public:
		Scene():m_finished(false) {}
		virtual ~Scene() {}

		virtual void pollEvents() {}
		virtual void update(float delta_time) {}
		virtual void render() {}
		inline bool isSceneFinished() {return m_finished;}
		bool m_return = false;
		
	};
	class SceneMenu : public Scene {
	public:
		//The scene menu will take a pointer, and whatever that happens inside this class
		//will also modify the outside pointer
		SceneMenu(Scene*& currentScenePtr);
		void pollEvents()override;
		void update(float delta_time)override;
		void render()override;

		// template <typename T>
		// void registerScene(const std::string& name)
		// {

		// 	std::cout << "Scene Manager: Registering Scene " << name << "\n";
		// 	m_Scenes.push_back(std::make_pair(name, []() {return new T(); }));

		// }
		
		void registerScene(const std::string& json_file);

		void setScene(const std::string& name);
		void nextScene();

		void handleSelection();
		void backToMenu();

	private:
		// Background
        RadialStarField rstarfield;
		MusicPlayer music;
		// sf::RectangleShape m_background;
		Composit::Fade* f_in;
		sf::Texture m_texture;
		sf::Font title_font;
		sf::Text title;
		SelectionMenu selection;
		//contains a collection of scenes
		Scene*& m_CurrentScenePtr;//it will be turned into an alias of an outsider
		//scene ptr, thanks to this, we can access the methods in the scene
		std::vector < std::pair<std::string, std::function<Scene*(json cfg)>>> m_Scenes;
		//we use std::function as a placeholder for the lambda
		//when we register, we register the name and its lambda
		std::pair<std::string, std::function<Scene* (json cfg)>>* m_sceneElement;
		friend void goBackToMainMenu();

		template <typename T>
		void registerScenePassJSON(const std::string& json_file)
		{
			json cfg2;
			std::cout << "Scene Manager: Registering Scene by JSON: " << json_file << "\n";
			m_Scenes.push_back(std::make_pair(json_file, [](json cfg2) {return new T(cfg2); }));

		}
		
	};
	void goBackToMainMenu();
	void goToGameOver();

}
