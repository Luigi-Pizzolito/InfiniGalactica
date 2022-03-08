#include "TextManager.h"
#include <vector>
#include <iostream>

TextManager::TextManager(sf::RenderWindow* m_window, sf::View* m_view, bool* s_key):m_window(m_window),m_view(m_view),s_key(s_key) {
    // Load and set font
    font.loadFromFile("res/Novel/LanaPixel.ttf");
    
    // Load current scene from JSON files
    loadScene();
}

TextManager::~TextManager() {
    scenes_p.clear();
}

void TextManager::loadScene() {
    TextPanel test(sf::String(L"你好，大家你们喜欢space adventure吗？ Hello, are you ready to play InfiniGalactica? If not you should hold on to your socks!  You really should play this otherwise imma whoops your lil' ass straight outta here you lil' who you think you are"),
							   font, fontSize, sf::Color::Cyan, m_window, m_view, s_key);
    scenes_p.push_back(test);
}

void TextManager::next() {
    if (scenes_p[scene_i].next()) {
        if (scene_i+1 < scenes_p.size()) {
            scene_i++;
        } else {
            std::cout << "finished displaying all panels\n";
        }
    }
}

void TextManager::tick() {
    scenes_p[scene_i].tick();
}

void TextManager::draw() {
    scenes_p[scene_i].draw();
}