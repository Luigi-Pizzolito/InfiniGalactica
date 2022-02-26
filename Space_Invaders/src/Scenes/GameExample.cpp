#include<iostream>
//External-Libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//STL-libs
#include <cstdlib>
#include <ctime>
//Group-Libs
#include "Application/Conways_Game_Of_Life.h"
///variables

int main() {

	//set up
	
	Game application(sf::Vector2i(200, 200), "Conway's Game of Life");

	while (application.isRunning()) {

		//updates the events and game states
		application.update();

		//clears-renders-displays objects
		application.render();




	}



}

