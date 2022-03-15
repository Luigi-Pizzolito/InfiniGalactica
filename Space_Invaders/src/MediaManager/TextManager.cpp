#include "TextManager.h"
#include <vector>
#include <iostream> //needed for color conversions
#include <fstream>

// todo: add fullscreen scrolling textpanel class alt for intro opening scene, credits etc

TextManager::TextManager(std::string scene, sf::RenderWindow *m_window, sf::View *m_view, bool *s_key) : file(scene), m_window(m_window), m_view(m_view), s_key(s_key)
{
    // Load and set font
    font.loadFromFile("res/Novel/LanaPixel.ttf");

    // Load current scene from JSON files
    loadScene();
}

TextManager::~TextManager()
{
    scenes_p.clear();
}

void TextManager::loadScene()
{
    // Load and parse JSON file
    std::ifstream ifs(file);
    json j = json::parse(ifs);
    // std::cout << std::setw(4) << j << "\n\n";

    // Iterate over parsed JSON array and objects and copy data to class
    for (size_t i = 0; i < j.size(); i++)
    {
        std::string text;
        std::string color;
        // Iterate over key-value pairs and set variables
        for (auto &[key, val] : j[i].items())
        {
            if (key == "text")
            {
                text = val;
            }
            else if (key == "color")
            {
                color = val;
            }
        }

        // load data to variables
        // Color parse
        char *clr = &*color.begin();
        int r, g, b;
        sscanf(clr, "%02x%02x%02x", &r, &g, &b);
        // String format conversion
        std::string str(text);
        sf::String sfTmp = sf::String::fromUtf8(str.begin(), str.end());
        // Create text panel and push to array
        TextPanel test(sf::String(sfTmp), sf::Color(r, g, b), font, fontSize, m_window, m_view, s_key);
        scenes_p.push_back(test);

        // std::cout << "[#" << color << "] " << text << "\n";
    }
}

bool TextManager::next()
{
    if (scenes_p[scene_i].next())
    {
        if (scene_i + 1 < scenes_p.size())
        {
            scene_i++;
            return false;
        }
        else
        {
            std::cout << "finished displaying all panels\n";
            return true;
        }
    }
    return false;
}

void TextManager::tick()
{
    scenes_p[scene_i].tick();
}

void TextManager::draw()
{
    scenes_p[scene_i].draw();
}