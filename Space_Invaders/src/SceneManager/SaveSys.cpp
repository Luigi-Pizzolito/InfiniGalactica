#include "SceneManager/SaveSys.h"
#include "Algorithms/MathUtils.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <filesystem>
#define SAVE_F       "res/save.dat"
#define SAVE_TEMPLT  "{\"scene\":\"level1\",\"scores\":{}}"_json

inline std::vector<uint8_t> SaveSys::read_vector_from_disk(std::string file_path) {
    std::ifstream instream(file_path, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    return data;
}

inline void SaveSys::write_vector_to_disk(std::vector<uint8_t> buffer, std::string file_path) {
    std::ofstream out(file_path, std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    out.close();
}


void SaveSys::newSave() {
    // load template json
    json j = SAVE_TEMPLT;
    // write binary ompressed json
    write_vector_to_disk(json::to_cbor(j), SAVE_F);
}

void SaveSys::saveState(std::string scene_name) {
    if (std::filesystem::exists(SAVE_F)) {
        // read binary compressed json
        json j = json::from_cbor(read_vector_from_disk(SAVE_F));
        // modify current scene name
        j["scene"] = scene_name;
        // write binary compressed json
        write_vector_to_disk(json::to_cbor(j), SAVE_F);
    } else {
        // if no save, create blank and call this function again
        newSave();
        saveState(scene_name);
    }
}

void SaveSys::saveLevel(std::string scene_name, size_t score) {
    if (std::filesystem::exists(SAVE_F)) {
        // read binary compressed json
        json j = json::from_cbor(read_vector_from_disk(SAVE_F));
        // modify the score array
        j["scores"][scene_name] = score;
        // write binary compressed json
        write_vector_to_disk(json::to_cbor(j), SAVE_F);
    } else {
        std::cout << "SaveSys: ERROR cannot save level without a save file!\n";
    }
}

std::string SaveSys::restoreState() {
    if (std::filesystem::exists(SAVE_F)) {
        // read binary compressed json
        json j = json::from_cbor(read_vector_from_disk(SAVE_F));
        std::cout << "SaveSys: restored state to: " << std::string(j["scene"]) << "\n";
        std::cout << j.dump() << "\n";
        // return last scene
        return std::string(j["scene"]);
    } else {
        // if no save, create blank and call this function again
        newSave();
        return restoreState();
    }
}

void SaveSys::clearState() {
    if (std::filesystem::exists(SAVE_F)) {
        remove(SAVE_F);
        newSave();
    }
}




PauseSc::PauseSc(sf::RenderWindow* window, const sf::View* view, bool* paused, std::string scene_name):window(window),view(view),paused(paused),scene_name(scene_name) {
    std::cout << "starting pause screen for " << scene_name << "\n";
    //bg
    bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    bg.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);
    bg.setPosition(view->getCenter());
    bg.setScale(2.0f,2.0f);
    bg.setFillColor(sf::Color(0,0,0,128));
    //selec
    selec = new SelectionMenu(window, view);
    selec->addOptions(std::vector<std::string> {"Back to Game", "Save and Exit"});
}

PauseSc::~PauseSc() {
    delete selec;
}

void PauseSc::update() {
    if (selec->selected) {
        std::string select = selec->selection();
        if (select == "Back to Game") {
            selec->selection_i = 0;
            (*paused) = false;
        } else
        if (select == "Save and Exit") {
            //! save game here: scene_name and score
            SaveSys::saveState(scene_name);
            returnToMenu = true;
        }
        selec->selected = false;
    }
}

void PauseSc::pre() {
    selec->selection_i = 0;
    selec->updateLayout();
}

bool PauseSc::draw() {
    bg.setPosition(view->getCenter());

    window->draw(bg);
    selec->draw(VectorMath::getViewPortTopLeftPos());
    return returnToMenu;
}

void PauseSc::handleInput(sf::Event event) {
    selec->handleInput(event);
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        selec->selection_i = 0;
        selec->selected = true;
    }
}