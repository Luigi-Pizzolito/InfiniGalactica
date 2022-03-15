#pragma once
#include "SceneManager/Scene.h"
#include "MediaManager/TextManager.h"
#include "Algorithms/StarField.h"
#include "MediaManager/MusicPlayer.h"

class Credits: public SceneManagement::Scene {
    private:

        // BGM
        MusicPlayer* music;

        // Background
        RadialStarField* rstarfield;

        //Input bools
        bool key_space = false;

        //Internal functions
        FSScrollTextManager* fs_text;

    public:
        Credits();
        ~Credits();

        void pollEvents()override;
        void update(float delta_time) override;
	    void render()override;
};