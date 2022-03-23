#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "SceneManager/SceneUtils/SelectionMenu.h"

#include <json.hpp>
using json = nlohmann::json;

class SaveSys {
    private:
        static inline std::vector<uint8_t> read_vector_from_disk(std::string file_path);
        static inline void write_vector_to_disk(std::vector<uint8_t> buffer, std::string file_path);

        static void newSave();
    public:
        SaveSys() = default;
        ~SaveSys() = default;
        static void saveState(std::string scene_name);
        static std::string restoreState();
        static void clearState();
        static void saveLevel(std::string scene_name, size_t score);
        static bool exists();
 };

class PauseSc {
    private:
        sf::RenderWindow* window;
        const sf::View* view;
        SelectionMenu* selec;

        bool returnToMenu = false;
        bool* paused;
        std::string scene_name;

        sf::RectangleShape bg;

    public:
        PauseSc(sf::RenderWindow* window, const sf::View* view, bool* paused, std::string scene_name); //todo add score here
        ~PauseSc();

        bool draw();
        void pre();
        void update();
        void handleInput(sf::Event event);
};