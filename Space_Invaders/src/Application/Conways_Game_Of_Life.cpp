#include "Conways_Game_Of_Life.h"
#include <cstdlib>
#include <ctime>

Game::Game(const sf::Vector2i& screen_dimensions, const char* app_name):Application(screen_dimensions,app_name)
{
	//random seed
	std::srand(std::time(nullptr));
	//Game Set up
	unsigned int buffer_size = m_videoMode.width * m_videoMode.height;

	//Important----------------------------------------------
	//1.-Dont create anything in the heap unless it is really required
	//2.-Any variable created in the heap must be deleted, if you create it here
	//dont forget to delete it in the ~Game(), otherwise this will cause memmory leaks
	
	m_pixels = new sf::RectangleShape[buffer_size];
	m_output = new int[buffer_size];//each pixel in a horizontal row
	m_state = new int[buffer_size];
	memset(m_output, 0, buffer_size * sizeof(int));//let every pixel=0
	memset(m_state, 0, buffer_size * sizeof(int));

	for (int y = 1; y < m_videoMode.height - 1; y++) {
		for (int x = 1; x < m_videoMode.width - 1; x++) {
			m_state[y * m_videoMode.width + x] = std::rand() % 2;//randomize the pixels life
			m_pixels[y * m_videoMode.width + x].setSize(sf::Vector2f(1.f, 1.f));
			m_pixels[y * m_videoMode.width + x].setPosition(sf::Vector2f((float)x, (float)y));
		}


	}


}

Game::~Game()
{
	//delete objects created in the Heap
	delete[] m_pixels;
	delete[] m_state;
	delete[] m_output;
}

void Game::pollEvents()
{
	//set our private member to the current event

	while (m_window->pollEvent(m_events)) {
		//window events
		switch (m_events.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			
			if (m_events.key.code == sf::Keyboard::Escape) {
				m_window->close();
			}
			break;

		default:
			break;
			
		}
		//player events
		//getPlayerInput();
	}
}

void Game::update()
{
	//Game Events
	pollEvents();
	//lambda function that captures by reference
	static auto cell = [&](int x, int y) {
		return m_output[y * m_videoMode.width + x];
	};
	//Game Logic for the Game Loop
	for (int i = 0; i < m_videoMode.width * m_videoMode.height; i++) {
		m_output[i] = m_state[i];
	}
	//x and y start from 1 due to the auto cells
	for (int y = 1; y < m_videoMode.height - 1; y++) {
		for (int x = 1; x < m_videoMode.width - 1; x++) {
			int n_Neighbours = cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
				cell(x - 1, y + 0) + 0 + cell(x + 1, y + 0) +
				cell(x - 1, y + 1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);
			if (cell(x, y) == 1) {
				m_state[y * m_videoMode.width + x] = n_Neighbours == 2 || n_Neighbours == 3;

			}
			else {
				m_state[y * m_videoMode.width + x] = n_Neighbours == 3;
			}
			if (cell(x, y) == 1) {
				m_pixels[y * m_videoMode.width + x].setFillColor(sf::Color::Cyan);

			}
			else {
				m_pixels[y * m_videoMode.width + x].setFillColor(sf::Color::Black);
			}

		}
	}


}

void Game::render()
{
	//clear the screen
	m_window->clear();
	//renders objects
	for (int i = 0; i < m_videoMode.width * m_videoMode.height; i++) {
		m_window->draw(m_pixels[i]);

	}
	//displays objects on the screen
	m_window->display();
}
