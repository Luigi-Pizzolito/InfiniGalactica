#include "TextManager.h"
#include <vector>

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
    // std::vector<TextPanel> scenes_gen;
    TextPanel test(sf::String(L"你好，大家你们喜欢space adventure吗？ Hello, are you ready to play InfiniGalactica? If not you should hold on to your socks!  You really should play this otherwise imma whoops your lil' ass straight outta here you lil' who you think you are"),
							   font, fontSize, sf::Color::Cyan, m_window, m_view, s_key);
    // scenes_gen.push_back(test);
    // scenes_p = new std::vector<TextManager>(scenes_gen);
    // scenes_gen.clear();
    scenes_p.push_back(&test);
}

void TextManager::next() {
    // test->next();
    // scenes_p.at(scene_i)->next();
}

void TextManager::tick() {
    // test->tick();
    // scenes_p.at(scene_i)->tick();
}

void TextManager::draw() {
    // test->draw();
    (scenes_p.at(0))->draw();
}