#pragma once
#include "Application.h"

//Example for Conways Game of Life
class Game:public Application{
	
private:
	//Game variables
	sf::RectangleShape* m_pixels = nullptr;
	int* m_output = nullptr;
	int* m_state = nullptr;
	
public:
	//Constructors and Destructors
	Game(const sf::Vector2i& screen_dimensions, const char* app_name);
	~Game();
	void pollEvents()override;
	void update()override;
	void render()override;


};