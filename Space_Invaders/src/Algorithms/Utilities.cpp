#include "Utilities.h"
namespace Control {
	Timer::Timer()
	{
		//No members are needed here
	}
	Timer::~Timer()
	{
		//Destructor created just for polymorfism
	}

	GameTimer::GameTimer(float duration):m_cycleduration(duration),m_counting(false)
	{

	}

	GameTimer::GameTimer():m_cycleduration(0.0f),m_counting(false)
	{

	}

	GameTimer::~GameTimer()
	{

	}

	void GameTimer::setDuration(float duration)
	{
		m_cycleduration = duration;
	}

	void GameTimer::start()
	{
		if (!m_counting) {
			m_start= m_start = std::chrono::steady_clock::now();
			m_counting = true;
		}
	}
	bool GameTimer::timeOut()
	{
		bool timeout = false;
		m_end= std::chrono::steady_clock::now();
		m_duration = m_end - m_start;
		//std::cout << m_duration.count() << "\n";
		if (m_counting) {
			if (m_duration.count() >= m_cycleduration) {
				timeout = true;
				m_counting = false;
			}
		
		}
		return timeout;
	}

}

namespace Debug {
	AutomaticTimer::AutomaticTimer()
	{
		m_start = std::chrono::steady_clock::now();
	}
	AutomaticTimer::~AutomaticTimer()
	{
		m_end = std::chrono::steady_clock::now();
		m_duration = m_end - m_start;
		float ms = m_duration.count() * 1000.0f;
		std::cout << "DebugAutomaticTimer: Time elapsed: " << ms << " ms" << "\n";
	}
	ManualTimer::ManualTimer()
	{

	}
	ManualTimer::~ManualTimer()
	{

	}
	void ManualTimer::start()
	{

		m_start = std::chrono::steady_clock::now();
	}
	void ManualTimer::stop()
	{
		m_end = std::chrono::steady_clock::now();
		m_duration = m_end - m_start;
		float ms = m_duration.count() * 1000.0f;
		std::cout << "DebugManualTimer: Time elapsed: " << ms << " ms" << "\n";
	}





	XAxis::XAxis(sf::RenderWindow* window, const sf::View* view, int division, int total):m_window(window),c_view(view) {
		int divs = total/division;
		lines = new sf::VertexArray(sf::LinesStrip,divs*2);
		for (int i = 0; i < divs; i+=2) {
			(*lines)[i].position   = sf::Vector2f(i*division,0);
			(*lines)[i+1].position = sf::Vector2f(i*division,view->getSize().y);
		}
	}

	XAxis::~XAxis() {
		delete lines;
	}

	void XAxis::draw() {
		m_window->draw(*lines);
	}
}