#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace SFX {
    extern sf::Music player;
    void play(const std::string file, float volume = 15.0f, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), float z = 0.0f);
};

namespace SFXlib {
    const std::string BulletShoot  (    "DefiniteShot5"    );
    const std::string BulletHit    (    "DefiniteHit"      );
    const std::string EnemyDestroy (    "DestroyMonster2"  );
};