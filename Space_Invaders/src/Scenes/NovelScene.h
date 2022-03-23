#pragma once
#include "SceneManager/Scene.h"
#include "MediaManager/TextManager.h"
#include "MediaManager/MusicPlayer.h"
// #include <vector>
// #include <string>
#include <json.hpp>
using json = nlohmann::json;

#include "SceneManager/SceneUtils/Composit.h"
#include "SceneManager/SaveSys.h"

class NovelLevel :public SceneManagement::Scene {

private:
	MusicPlayer* music;
	float lvl_p = 0.0f;
    //Fonts
    // sf::Font font;
	Composit::Fade* f_in;
	Composit::Fade* f_out;

	json cfg;

	PauseSc* pSc;
	bool paused = false;
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
	NovelLevel(json cfg);
	~NovelLevel();
	void pollEvents()override;
	void update(float delta_time) override;
	void render()override;
};
