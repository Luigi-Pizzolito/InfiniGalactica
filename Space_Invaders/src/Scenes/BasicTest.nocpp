#include<iostream>
//STL-libs
#include <cstdlib>
#include <ctime>
//Group-Libs
#include "Application/BasicShooter.h"
#include "Application/BasicNovel.h"
#include "SceneManager/MusicPlayer.h"
///variables
//Added by Daniel 02.27 10:00 AM
int main() {

	//Client Side Application
	ShooterGame application(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2), "Shooter Test");
	// NovelGame application(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2.5, sf::VideoMode::getDesktopMode().height/2.5), "Novel Test");
	MusicPlayer* music = new MusicPlayer("song1", true);
	// todo: add class to draw HUD

	//Game Loop
	while (application.isRunning()) {

		//updates the events and game states
		application.update();

		//clears-renders-displays objects
		application.render();

	}

}
