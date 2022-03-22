#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <string>
class SFX {
    private:
        // number of simultaneous SFX players to keep baseline
        static const size_t num_players = 8;
        // internal variables for keeping loaded samples, players, sfxlib
        std::map<std::string, sf::SoundBuffer> samples;
        std::vector<sf::Sound> players;
        // internal method for fetching available player
        static sf::Sound* getAvailPlayer();
    public:
        // declare loadLib and play functions
        static void loadLib();
        static void play(const std::string fx, float volume = 8.0f, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), float z = 0.0f);
    private:
        // instantiator for singleton class and private con/destructor
        SFX();
        ~SFX();
        static SFX& instance();
        // override operators to ensure singleton class in non-copiable
        SFX(const SFX&)=delete;
        SFX& operator=(const SFX&)=delete;
        SFX(SFX&&)=delete;
        SFX& operator=(SFX&&)=delete;
};

// utility namespace for easily accesing SFXlib sfx with IntelliSense
namespace SFXlib {
    const std::string BulletShoot  (    "BulletShoot"    );
    const std::string BulletReload (   "BulletReload"    );
    const std::string BulletHit    (    "BulletHit"      );
    const std::string EnemyDestroy (    "EnemyDestroy"   );
    const std::string Selec        (    "Selec"          );
    const std::string Enter        (    "Enter"          );
    const std::string GameOver     (    "GameOver"       );
    // const std::string Miku_L1      (    "Miku_L1"        );
    // const std::string Miku_L2      (    "Miku_L2"        );
    // const std::string Miku_L3      (    "Miku_L3"        );
    // const std::string Miku_L4      (    "Miku_L4"        );
    // const std::string Miku_L5      (    "Miku_L5"        );
};