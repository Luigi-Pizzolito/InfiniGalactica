#include "TextManager.h"
#include <vector>
#include <iostream> //needed for color conversions
#include <fstream>

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
        std::string actor = "";
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
            } else if (key == "actor") {
                actor = val;
            }
        }

        // load data to variables
        // Color parse
        char *clr = &*color.begin();
        int r, g, b;
        std::sscanf(clr, "%02x%02x%02x", &r, &g, &b);
        // String format conversion
        std::string str(text);
        sf::String sfTmp = sf::String::fromUtf8(str.begin(), str.end());
        std::string str2(actor);
        sf::String sfTmp2 = sf::String::fromUtf8(str2.begin(), str2.end());
        // Create text panel and push to array
        TextPanel test(sf::String(sfTmp), sf::String(sfTmp2), sf::Color(r, g, b), font, fontSize, m_window, m_view, s_key);
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









FSScrollTextManager::FSScrollTextManager(std::string scene, sf::RenderWindow *m_window, sf::View *m_view, bool *s_key) : file(scene), m_window(m_window), m_view(m_view), s_key(s_key)
{
    // Load and set font
    font.loadFromFile("res/Novel/LanaPixel.ttf");
    fs_text.setFont(font);
    fs_text.setFillColor(sf::Color::White);
    fs_text.setCharacterSize(fontSize);
    fs_text.setLineSpacing(line_spacing);

    // Load current scene from JSON files
    loadScene();

    // Set initial position
    // t_pos = sf::Vector2f(-vert_margin*1.3f,-horz_margin);
    t_pos = sf::Vector2f(m_view->getCenter().x,m_view->getSize().y-4*vert_margin);
    fs_text.setOrigin(sf::Vector2f(fs_text.getGlobalBounds().width/2,0.0f));
}

FSScrollTextManager::~FSScrollTextManager() {}


void FSScrollTextManager::loadScene() {
    // Load and parse JSON file
    std::ifstream ifs(file);
    json j = json::parse(ifs);
    // String format conversion
    std::string str(j["text"]);
    sf::String sfTmp = sf::String::fromUtf8(str.begin(), str.end());
    // Set text, adding line wrap
    fs_text.setString(addLineWrap(sf::String(sfTmp)));
    fs_text.setPosition(t_pos);
}

sf::String FSScrollTextManager::addLineWrap(sf::String string) {
    // Word wrap algorithim, finding the display length and adding \n or \31 alternatively, to add line breaks and separator \31 to indicate next panel
	unsigned width = m_view->getSize().x - 2*horz_margin;
	unsigned currentOffset = 0;
	bool firstWord = true;
	std::size_t wordBegining = 0;

	for (std::size_t pos(0); pos < string.getSize(); ++pos)
	{
		auto currentChar = string[pos];
		if (currentChar == '\n')
		{
			currentOffset = 0;
			firstWord = true;
			continue;
		}
		else if (currentChar == ' ')
		{
			wordBegining = pos;
			firstWord = false;
		}

		auto glyph = font.getGlyph(currentChar, fontSize, false);
		currentOffset += glyph.advance;

		if (!firstWord && currentOffset > width)
		{
			pos = wordBegining;
			string[pos] = '\n';
			firstWord = true;
			currentOffset = 0;
		}
	}

    return string;
}


bool FSScrollTextManager::tick() {
    // Scroll text
    t_pos.y-= *s_key ? hold_s_boost : 1;
    fs_text.setPosition(t_pos);

    // Check if text is done scrolling
    // std::cout << "text x: " << fs_text.getGlobalBounds().top+fs_text.getGlobalBounds().height << "\tView Thres: " << m_view->getSize().y/4 << "\n";
    if (fs_text.getGlobalBounds().top+fs_text.getGlobalBounds().height < m_view->getSize().y/3.5) {
        std::cout << "done scrolling!\n";
        return true;
    } else {
        return false;
    }
}

void FSScrollTextManager::draw() {
    m_window->draw(fs_text);
}