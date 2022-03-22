#pragma once
#include <SFML/Audio.hpp>
#include <json.hpp>
using json = nlohmann::json;
#include <string>

class MusicPlayer {
    private:
        sf::Music player;
        json cfg;

        void setLoop(int i);
        void noLoop();

    public:
        MusicPlayer(const std::string song, bool autoPlay = false, float vol = 100.0f);
        ~MusicPlayer();

        void play();
        void pause();
        void stop();
        float position() {return player.getPlayingOffset().asSeconds();}
        void update(float levelProgress);
};