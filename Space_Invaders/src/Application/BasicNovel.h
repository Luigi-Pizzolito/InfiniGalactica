#pragma once
#include "Application.h"
#include "SceneManager/TextPanel.h"
// #include <vector>
// #include <string>

class NovelGame :public Application {

private:
    //Fonts
    sf::Font font;

	//Textures
	sf::Texture dialog_overlay;

	//Background

	//Camera

    //Input bools
    bool key_space = false;

    // Internal functions
    TextPanel* text_panel;

public:
	//Constructors and Destructors
	NovelGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~NovelGame();
	void pollEvents()override;
	void update()override;
	void render()override;

    void drawText();
};