#include "Application.h"

//Implemented by Daniel 02.27 8:10 AM
Application::Application(const sf::Vector2i& screen_dimensions,const char* app_name):
	m_videoMode(screen_dimensions.x,screen_dimensions.y)
{
	//Creates window in the Heap
	m_window=new sf::RenderWindow(m_videoMode, app_name, sf::Style::Default);
	m_window->setFramerateLimit(60);

	// Luigi: Added sf:View because that has a .move() function for scrolling
	m_view =new sf::View();
	m_view->reset(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	m_window->setView(*m_view);
}
//Implemented by Daniel 02.27 9:10 AM
Application::~Application()
{
	//Window deletion
	delete m_window;
	delete m_view;
}
//Implemented by Daniel 02.27 8:16 AM
const bool Application::isRunning()const
{
	return m_window->isOpen();
}
//Implemented by Daniel 02.27 8:18 AM
void Application::pollEvents()
{
	//set our private member to the current event


}
//Implemented by Daniel 02.27 8:21 AM
void Application::update()
{
	//Poll events first
	//pollEvents();

}
//Implemented by Daniel 02.27 8:24 AM
void Application::render()
{
	//clear->draw(only sets the internal changes)->display(shows the changes)
	
	//m_window->clear();
	
	//m_window->draw(object);

	//m_window->display();

}

