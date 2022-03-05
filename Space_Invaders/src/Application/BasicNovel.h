#pragma once
#include "Application.h"
#include <vector>
#include <string>

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
    size_t panel_i = 0;
    std::vector<sf::String>* panel_p;
    static std::vector<sf::String> wrapTextPanelise(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold = false);
    bool next();
    std::string ToUTF8(const sf::String &original);

public:
	//Constructors and Destructors
	NovelGame(const sf::Vector2i& screen_dimensions, const char* app_name);
	~NovelGame();
	void pollEvents()override;
	void update()override;
	void render()override;

    void drawText();
};