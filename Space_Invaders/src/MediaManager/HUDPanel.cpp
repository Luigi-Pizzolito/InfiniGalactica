#include "MediaManager/HUDPanel.h"
#include <cmath>
#include <iostream>

HUDPanel::HUDPanel(sf::RenderWindow* window, const sf::View* view, Player* player, const size_t* player_score, const float* level_p):m_window(window),c_view(view),player(player),player_score(player_score),level_p(level_p) {
    // Initialise drawing elements
    font.loadFromFile("res/Novel/LanaPixel.ttf");
    // score text
    score_t.setFont(font);
    score_t.setCharacterSize(fontSize);
    score_t.setString("000000"); //placeholder needed for the calculations below
    hs_w = score_t.getLocalBounds().width;
    // hud bg
    hud_bg.setOutlineThickness(border);
    hud_bg.setPointCount(5);
    hud_bg.setPoint(0, sf::Vector2f(c_view->getSize().x - hs_w - fontSize, 0.0f));
    hud_bg.setPoint(1, sf::Vector2f(c_view->getSize().x, 0.0f));
    hud_bg.setPoint(2, sf::Vector2f(c_view->getSize().x, fontSize+padding));
    hud_bg.setPoint(3, sf::Vector2f(c_view->getSize().x - hs_w - padding, fontSize+padding));
    hud_bg.setPoint(4, sf::Vector2f(c_view->getSize().x - hs_w - fontSize, padding+fontSize/2));
    // hud bars bg
    hud_bars_bg1.setOutlineThickness(border);
    hud_bars_bg1.setSize(sf::Vector2f(c_view->getSize().x - hs_w - fontSize - border, ((padding+fontSize/2)/2)));
    hud_bars_bg2.setOutlineThickness(border);
    hud_bars_bg2.setSize(sf::Vector2f(c_view->getSize().x - hs_w - fontSize - border, ((padding+fontSize/2)/2)));
    // bars
    h_bar.setOutlineThickness(0);
    l_bar.setOutlineThickness(0);
}

HUDPanel::~HUDPanel() {

}


void HUDPanel::draw() {
    // hide hud alpha
    int hud_a = (player->getSprite().getPosition().y <= 3*fontSize+2*padding) ? std::floor(2*(player->getSprite().getPosition().y-(fontSize+2*padding))) : 255 ;  // threshold and scale player proximity to hud
    hud_a = hud_a > 255 ? 255 : (hud_a < 0 ? 0 : hud_a);  // Clamp to 0-255
    // hud bg
    hud_bg.setPosition(c_view->getCenter() - c_view->getSize()/2.0f);
    hud_bg.setFillColor(sf::Color(0,0,0,hud_a));
    hud_bg.setOutlineColor(sf::Color(128,128,128,hud_a));
    m_window->draw(hud_bg);
    // hud bars bg
    hud_bars_bg1.setPosition(c_view->getCenter() - c_view->getSize()/2.0f);
    hud_bars_bg1.setFillColor(sf::Color(0,0,0,hud_a));
    hud_bars_bg1.setOutlineColor(sf::Color(128,128,128,hud_a));
    m_window->draw(hud_bars_bg1);
    hud_bars_bg2.setPosition(c_view->getCenter() - c_view->getSize()/2.0f + sf::Vector2f(0.0f,((padding+fontSize/2)/2)));
    hud_bars_bg2.setFillColor(sf::Color(0,0,0,hud_a));
    hud_bars_bg2.setOutlineColor(sf::Color(128,128,128,hud_a));
    m_window->draw(hud_bars_bg2);
    // bars
    float h = (float)player->getHP() / (float)player->getMaxHP();
    h_bar.setPosition(c_view->getCenter() - c_view->getSize()/2.0f + sf::Vector2f(border, 0.0f));
    h_bar.setSize(sf::Vector2f((c_view->getSize().x - hs_w - fontSize - 2*border)*h, ((padding+fontSize/2)/2)) - sf::Vector2f(0.0f, border));
    h_bar.setFillColor(sf::Color(180,0,0,hud_a));
    m_window->draw(h_bar);
    //todo link lvl p%
    float l = 0.86f;
    l_bar.setPosition(c_view->getCenter() - c_view->getSize()/2.0f + sf::Vector2f(border, 0.0f) + sf::Vector2f(0.0f,((padding+fontSize/2)/2)));
    l_bar.setSize(sf::Vector2f((c_view->getSize().x - hs_w - fontSize - 2*border)*l, ((padding+fontSize/2)/2)));
    l_bar.setFillColor(sf::Color(0,0,180,hud_a));
    m_window->draw(l_bar);
    // score text
    char s_str[7];
    std::snprintf(s_str, 7, "%06d", (int)*player_score);
    score_t.setString(s_str);
    score_t.setFillColor(sf::Color(255,255,255,hud_a));
    score_t.setOrigin(sf::Vector2f(score_t.getLocalBounds().width, 0.0f));
    score_t.setPosition(c_view->getCenter() - c_view->getSize()/2.0f + sf::Vector2f(c_view->getSize().x-padding, -padding));
    m_window->draw(score_t);
}