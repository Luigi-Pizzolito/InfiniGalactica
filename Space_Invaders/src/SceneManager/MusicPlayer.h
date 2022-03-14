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
        MusicPlayer(const std::string song, bool autoPlay = false);
        ~MusicPlayer();

        void play();
        void pause();
        float position() {return player.getPlayingOffset().asSeconds();}
        void update(float levelProgress);
};