#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum class STATES {
	PRESSED = 0, RELEASED
};

class Application {
	//members for SFML
	//can be accessed by the Game
protected:
	sf::RenderWindow* m_window = nullptr;
	sf::View* m_view = nullptr; // Luigi: Added sf:View because that has a .move() function for scrolling
	sf::VideoMode m_videoMode;
	sf::Event m_events;

public:
	//Constructors and Destructors
	Application(const sf::Vector2i& screen_dimensions, const char* app_name);
	virtual ~Application();

	//Public Methods
	const bool isRunning()const;
	//PollEvents
	virtual void pollEvents();
	//Update is where we write the logic of our Application
	virtual void update();
	//Render only deals with graphical stuff
	virtual void render();


};