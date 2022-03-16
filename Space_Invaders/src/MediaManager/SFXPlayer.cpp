#include "MediaManager/SFXPlayer.h"
#include <iostream>

sf::Music SFX::player;

void SFX::play(const std::string file, float volume, sf::Vector2f position, float z) {
    SFX::player.setVolume(volume);
    SFX::player.setPosition(position.x, position.y, z);
    if (!SFX::player.openFromFile("res/Music/sfx/"+file+".ogg"))
    {
        std::cout << "Failed to open: " << file << "\n";
    }
    // std::cout << "SFX: play: " << file << "\n";
    SFX::player.play();
}