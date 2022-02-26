#include "Application.h"


Application::Application(const sf::Vector2i& screen_dimensions,const char* app_name):
	m_videoMode(screen_dimensions.x,screen_dimensions.y)
{
	//Creates window in the Heap
	m_window=new sf::RenderWindow(m_videoMode, app_name, sf::Style::Default);
	m_window->setFramerateLimit(60);
}

Application::~Application()
{
	//Window deletion
	delete m_window;
}

const bool Application::isRunning()const
{
	return m_window->isOpen();
}

void Application::pollEvents()
{
	//set our private member to the current event


}

void Application::update()
{
	//Poll events first
	//pollEvents();

}

void Application::render()
{
	//clear->draw(only sets the internal changes)->display(shows the changes)
	
	//m_window->clear();
	
	//m_window->draw(object);

	//m_window->display();

}

