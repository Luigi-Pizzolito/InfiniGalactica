#include "SelectionMenu.h"
#include <iostream>

SelectionMenu::SelectionMenu(sf::RenderWindow* window, const sf::View* view):m_window(window),c_view(view) {
    // selection_t.setString("Continue\nNew Game\nEndless Mode\nOptions");
    font.loadFromFile("res/Novel/LanaPixel.ttf");
    selection_t.setFont(font);
    selection_t.setCharacterSize(font_s);
    selection_t.setFillColor(sf::Color::White);
    pointer_t.setFont(font);
    pointer_t.setCharacterSize(font_s);
    pointer_t.setFillColor(sf::Color::White);
    pointer_t.setString(L"");
}

SelectionMenu::~SelectionMenu() {}


void SelectionMenu::addOptions(std::string single_option) {
    options.push_back(single_option);
    updateLayout();
}

void SelectionMenu::addOptions(std::vector<std::string> multiple_option) {
    for(auto& single_option : multiple_option) {
        options.push_back(single_option);
    }
    updateLayout();
}

void SelectionMenu::updateLayout() {
    std::string opts = "";
    for(auto& item : options) {
        opts += item + "\n";
    }
    selection_t.setString(opts);
    selection_t.setOrigin(sf::Vector2f((-c_view->getSize().x/2)+(selection_t.getGlobalBounds().width/4), -c_view->getSize().y/2));

    pointer_t.setOrigin(sf::Vector2f((-c_view->getSize().x/2)+(selection_t.getGlobalBounds().width/4)+pointer_t.getGlobalBounds().width+10, (-c_view->getSize().y/2)-selection_i*selec_off));
}

void SelectionMenu::draw() {
    m_window->draw(selection_t);
    m_window->draw(pointer_t);
}

void SelectionMenu::handleInput(sf::Event event) {
    // Increase or decrease selection, no looping.
    if (event.key.code == sf::Keyboard::S && selection_i < options.size()-1) {
        selection_i++;
    } else
    if (event.key.code == sf::Keyboard::W && selection_i != 0) {
        selection_i--;
    }
    updateLayout();

    if (event.key.code == sf::Keyboard::Enter) {
        // std::cout << "Selected " << options[selection_i] << "\n";
        // func_ptr(options[selection_i]);
        selected = true;
    }
}