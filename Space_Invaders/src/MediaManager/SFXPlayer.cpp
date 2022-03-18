#include "MediaManager/SFXPlayer.h"
#include <fstream>
#include <json.hpp>
using json = nlohmann::json;
#include <iostream>

SFX::SFX() {
    // allocate for initial min. audio players
    players.reserve(num_players);
}

SFX::~SFX() {
    // clear samples and players
    players.clear();
    samples.clear();
}

SFX& SFX::instance() {
    // create singleton variable SFX instance
    static SFX inst;
    return inst;
}

void SFX::loadLib() {
    // Load the audios for the SFX library from JSON spec
    json cfg;
    std::ifstream ifs ("res/Music/sfx/SFXlib.json");
    cfg = json::parse(ifs);
    // iterate over entries and load each sample
    SFX* sfx = &SFX::instance();
    for (const auto &[sample, path] : cfg.items()) {
        // for each sample, load into a buffer and add to samples lib
        sfx->samples.insert({sample, sf::SoundBuffer()});
        if (!sfx->samples[sample].loadFromFile(path))
        {
            sfx->samples.erase(sfx->samples.find(sample));
            std::cout << "SFX: ERROR Loading " << sample << "->" << path << " into buffer vect.\n";
        } else {
            std::cout << "SFX: Loaded [" +std::to_string(sfx->samples[sample].getSampleCount())+ "] " << sample << "\n";
        }
    }
    std::cout << "SFX: SFXlib loaded.\n";
}

sf::Sound* SFX::getAvailPlayer() {
    // find or create available player
    std::vector<sf::Sound>* players = &SFX::instance().players;
    int location = -1;
    for (int i = 0; i < players->size(); i++) {
        // find the first available player
        if (players->at(i).getStatus() != sf::Sound::Playing && location == -1) {
            location = i;
        } else
        if (players->at(i).getStatus() != sf::Sound::Playing && location != -1 && players->size() > num_players) {
            // if we find inactive players beyond the baseline number of players; remove/prune them.
            players->erase(players->begin()+i);
        }
    }
    if (location ==-1 || players->size() == 0) {
        // if no available players, add player
        players->push_back(sf::Sound());
        location = players->size()-1;
    }
    // return the available player
    std::cout << "SFX: [" << location+1 << "/" << players->size() << "] ";
    return &players->at(location);
}

void SFX::play(const std::string fx, float volume, sf::Vector2f position, float z) {
    // get available player, set parameters and play sound
    sf::Sound* player = SFX::getAvailPlayer();
    player->resetBuffer();
    player->setBuffer(SFX::instance().samples[fx]);
    player->setVolume(volume);
    player->setPosition(position.x, position.y, z);
    std::cout << "Playing [" << SFX::instance().samples[fx].getSampleCount() << "] " << fx << "\n";
    player->play();
}