#include "MusicPlayer.h"
#include <fstream>
#include <cmath>
#include <iostream>

MusicPlayer::MusicPlayer(const std::string song, bool autoPlay) {
    // load song parameters from JSON
    // Read JSON file info and parse to store in internal object
    std::ifstream ifs(std::string("res/Music/")+song+std::string(".json"));
    cfg = json::parse(ifs);
    // std::cout << "Loaded json: " << cfg["file"] << "\n";

    // open music file
    if (!player.openFromFile(cfg["file"]))
    {
        std::cout << "Failed to open: " << cfg["file"] << "\n";
    }

    // set initial loop
    player.setVolume(100);
    if (cfg["loop_points"].size() > 0) {
        setLoop(0);
    } else {
        noLoop(); //sets the correct full loop boundaries
        player.setLoop(true);
    }

    // autoplay if autoPlay
    if (autoPlay) {
        play();
    }
}

MusicPlayer::~MusicPlayer() {
    player.stop();
}

void MusicPlayer::setLoop(int i) {
    // Utility function to clean up ugly syntax
    // std::cout << "Looping from " << cfg["loop_points"][i]["off"] << " to " << (float)cfg["loop_points"][i]["off"]+(float)cfg["loop_points"][i]["len"] << "\n";
    player.setLoopPoints(sf::Music::TimeSpan(sf::seconds(cfg["loop_points"][i]["off"]), sf::seconds(cfg["loop_points"][i]["len"])));
    player.setLoop(true);
}

void MusicPlayer::noLoop() {
    player.setLoopPoints(sf::Music::TimeSpan(sf::seconds(0.0f), player.getDuration()));
    player.setLoop(false);
}



void MusicPlayer::play() {
    // Start the sf::Music player
    player.play();
}

void MusicPlayer::pause() {
    // Pause the sf::Music player
    player.pause();
}

void MusicPlayer::stop() {
    // Stop the sf::Music player
    player.stop();
}

void MusicPlayer::update(float levelProgress) {
    // Set the loop points, scaling accordingly to the level progress and number of loops.
    // std::cout << "lvl progress: " << levelProgress << "\n";
    if ( levelProgress < 1.0f) {
        // if in loop scaling range and there are loops
        if (cfg["loop_points"].size() > 0) {
            float threshold = 1.0f/(float)cfg["loop_points"].size();  // calculate percentage thresholds where the loop should be changed to the next one
            int loop_i = std::floor(levelProgress/threshold);  // calculate what the current loop should be
            if (loop_i > cfg["loop_points"].size()-1) {loop_i = cfg["loop_points"].size()-1;} // safe guard to not access past array index
            setLoop(loop_i);
            // std::cout << "current loop index: " << loop_i << "\n\n";
        }
    } else {
        // Otherwise if level complete stop loop and let it end
        noLoop();
        // std::cout << "end loop\n\n";
    }
}