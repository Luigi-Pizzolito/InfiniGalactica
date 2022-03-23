#pragma once
#include "SceneManager/Scene.h"
#include "Algorithms/StarField.h"
#include "MediaManager/MusicPlayer.h"
#include "SceneManager/SceneUtils/Composit.h"

#include <json.hpp>
using json = nlohmann::json;

class GameOver: public SceneManagement::Scene {
    private:

        // BGM
        MusicPlayer* music;
        Composit::Fade* f_in;
        // Background
        RadialStarField* rstarfield;
        sf::Font title_font;
        sf::Text title;
        sf::Text sub;

        //Input bools

        //Internal functions

    public:
        GameOver(json cfg);
        ~GameOver();

        void pollEvents()override;
        void update(float delta_time) override;
	    void render()override;
};