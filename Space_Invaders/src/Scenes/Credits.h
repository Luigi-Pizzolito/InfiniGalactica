#pragma once
#include "SceneManager/Scene.h"
#include "MediaManager/TextManager.h"
#include "MediaManager/MusicPlayer.h"

class Credits: public SceneManagement::Scene {
    private:

        // BGM
        MusicPlayer* music;

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