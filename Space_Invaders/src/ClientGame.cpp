//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include<iostream>
//STL-libs
#include <cstdlib>
#include <ctime>
//Group-Libs
#include "Application/BasicShooter.h"

///variables
int main() {

	//Client Side Application
	ShooterGame InfiniGalactica(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2), "InfiniGalactica");
	std::cout<< "Running InfiniGalactica at " << sf::VideoMode::getDesktopMode().width/2 << "x" << sf::VideoMode::getDesktopMode().height/2 << "px\n";
	//Game Loop
	while (InfiniGalactica.isRunning()) {
	
		//updates the events and game states
		InfiniGalactica.update();

		//clears-renders-displays objects
		InfiniGalactica.render();

	}

}
