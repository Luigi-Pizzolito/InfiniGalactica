#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <ctime>
///variables
int* m_output;
int* m_state;

int ScreenWidth = 200;
int ScreenHeight = 200;
sf::RectangleShape* pixel;
int main() {

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Square Movement	", sf::Style::Default);
	window.setFramerateLimit(60);
	//setup
	pixel = new sf::RectangleShape[ScreenWidth * ScreenHeight];
	//get an array of rectangle

	std::srand(std::time(nullptr));

	m_output = new int[ScreenWidth * ScreenHeight];//each pixel in a horizontal row
	m_state = new int[ScreenWidth * ScreenHeight];
	memset(m_output, 0, ScreenWidth * ScreenHeight * sizeof(int));//let every pixel=0
	memset(m_state, 0, ScreenWidth * ScreenHeight * sizeof(int));

	for (int y = 1; y < ScreenHeight - 1; y++) {
		for (int x = 1; x < ScreenWidth - 1; x++) {
			m_state[y * ScreenWidth + x] = std::rand() % 2;//randomize the pixels life
			pixel[y * ScreenWidth + x].setSize(sf::Vector2f(1.f, 1.f));
			pixel[y * ScreenWidth + x].setPosition(sf::Vector2f((float)x, (float)y));
		}


	}
	auto cell = [&](int x, int y) {
		return m_output[y * ScreenWidth + x];
	};

	while (window.isOpen()) {
		sf::Event appevent;
		while (window.pollEvent(appevent)) {
			if (appevent.type == sf::Event::Closed) {
				window.close();
			}
			if (appevent.type == sf::Event::KeyPressed && appevent.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}

		for (int i = 0; i < ScreenWidth * ScreenHeight; i++) {
			m_output[i] = m_state[i];
		}
		//x and y start from 1 due to the auto cells
		for (int y = 1; y < ScreenHeight - 1; y++) {
			for (int x = 1; x < ScreenWidth - 1; x++) {
				int n_Neighbours = cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
					cell(x - 1, y + 0) + 0 + cell(x + 1, y + 0) +
					cell(x - 1, y + 1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);
				if (cell(x, y) == 1) {
					m_state[y * ScreenWidth + x] = n_Neighbours == 2 || n_Neighbours == 3;

				}
				else {
					m_state[y * ScreenWidth + x] = n_Neighbours == 3;
				}
				if (cell(x, y) == 1) {
					pixel[y * ScreenWidth + x].setFillColor(sf::Color::Cyan);

				}
				else {
					pixel[y * ScreenWidth + x].setFillColor(sf::Color::Black);
				}

			}
		}

		//update
		window.clear();
		for (int i = 0; i < ScreenWidth * ScreenHeight; i++) {
			window.draw(pixel[i]);

		}

		window.display();
		//draw

	}

}


//function implementation


