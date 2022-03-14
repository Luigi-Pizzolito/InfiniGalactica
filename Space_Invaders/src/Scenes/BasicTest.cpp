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
	// ShooterGame application(sf::Vector2i(sf::VideoMode::getDesktopMode().width/4, sf::VideoMode::getDesktopMode().height/4), "Shooter Test");
	NovelGame application(sf::Vector2i(320*2, 240*2), "Novel Test");

	// todo: add music class

	//Game Loop
	while (application.isRunning()) {

		//updates the events and game states
		application.update();

		//clears-renders-displays objects
		application.render();

	}

}
