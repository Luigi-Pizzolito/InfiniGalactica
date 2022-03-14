#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include<iostream>
//STL-libs
#include <cstdlib>
#include <ctime>
//Group-Libs
#include "Application/BasicShooter.h"
#include "Application/BasicNovel.h"
///variables
//Added by Daniel 02.27 10:00 AM
int main() {

	//Client Side Application
	ShooterGame InfiniGalactica(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2,
		sf::VideoMode::getDesktopMode().height/2), "Shooter Test");
	// NovelGame application(sf::Vector2i(320*2, 240*2), "Novel Test");
	
	//Game Loop
	while (InfiniGalactica.isRunning()) {
	
		//updates the events and game states
		InfiniGalactica.update();

		//clears-renders-displays objects
		InfiniGalactica.render();

	}

}
