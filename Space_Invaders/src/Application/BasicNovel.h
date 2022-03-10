#pragma once
#include "Application.h"
#include "SceneManager/TextManager.h"
// #include <vector>
// #include <string>

//Class Implemented by Luigi 06.03 00:35
class NovelGame :public Application {

private:
    //Fonts
    // sf::Font font;

	//Textures
	// sf::Texture dialog_overlay;

	//Background

	//Camera

    //Input bools
    bool key_space = false;

    // Internal functions
    // TextPanel* text_panel;
	TextManager* text_panel;

public:
	//Constructors and Destructors
	NovelGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~NovelGame();
	void pollEvents()override;
	void update()override;
	void render()override;
};