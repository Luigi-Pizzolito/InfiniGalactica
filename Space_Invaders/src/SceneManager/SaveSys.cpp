#include "SceneManager/SaveSys.h"
#include "Algorithms/MathUtils.h"
#include <iostream>

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