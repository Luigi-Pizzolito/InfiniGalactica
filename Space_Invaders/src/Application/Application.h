#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//Class Implemented by Daniel 02.27 8:00 AM
enum class STATES {
	PRESSED = 0, RELEASED
};
//Class Implemented by Daniel 02.27 8:01 AM
class Application {
	//members for SFML
	//can be accessed by the Game
protected:
	//Implemented by Daniel 02.27 8:03 AM
	sf::RenderWindow* m_window = nullptr;
	sf::View* m_view = nullptr; // Luigi: Added sf:View because that has a .move() function for scrolling
	sf::VideoMode m_videoMode;

public:
	//Implemented by Daniel 02.27 8:10 AM
	//Constructors and Destructors
	Application(const sf::Vector2i& screen_dimensions, const char* app_name);
	virtual ~Application();
	//Implemented by Daniel 02.27 8:15 AM
	//Public Methods
	const bool isRunning()const;
	//Implemented by Daniel 02.27 8:17 AM
	//PollEvents
	virtual void pollEvents();
	//Implemented by Daniel 02.27 8:20 AM
	//Update is where we write the logic of our Application
	virtual void update();
	//Implemented by Daniel 02.27 8:22 AM
	//Render only deals with graphical stuff
	virtual void render();


};
