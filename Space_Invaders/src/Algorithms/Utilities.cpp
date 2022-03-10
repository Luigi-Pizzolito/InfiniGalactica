#include "Utilities.h"
namespace Control {
	//Implemented by Daniel 03.07 10:02 AM
	Timer::Timer()
	{
		//No members are needed here
	}
	//Implemented by Daniel 03.07 10:02 AM
	Timer::~Timer()
	{
		//Destructor created just for polymorfism
	}
	//Implemented by Daniel 03.07 10:12 AM
	DebugAutomaticTimer::DebugAutomaticTimer()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}
	//Implemented by Daniel 03.07 10:14 AM
	DebugAutomaticTimer::~DebugAutomaticTimer()
	{
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;
		float ms = m_duration.count() * 1000.0f;
		std::cout << "Time elapsed: " << ms << " ms" << "\n";
	}
	//Implemented by Daniel 03.07 10:21 AM
	DebugManualTimer::DebugManualTimer()
	{

	}
	//Implemented by Daniel 03.07 10:21 AM
	DebugManualTimer::~DebugManualTimer()
	{

	}
	//Implemented by Daniel 03.07 10:22 AM
	void DebugManualTimer::start()
	{
		
		m_start = std::chrono::high_resolution_clock::now();
	}
	//Implemented by Daniel 03.07 10:23 AM
	void DebugManualTimer::stop()
	{
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;
		float ms = m_duration.count() * 1000.0f;
		std::cout << "Time elapsed: " << ms << " ms" << "\n";
	}
	//Implemented by Daniel 03.07 10:26 AM
	GameTimer::GameTimer(float duration):m_cycleduration(duration),m_counting(false)
	{

	}
	//Implemented by Daniel 03.07 10:27 AM
	GameTimer::~GameTimer()
	{

	}
	//Implemented by Daniel 03.07 10:28 AM
	void GameTimer::start()
	{
		if (!m_counting) {
			m_start= m_start = std::chrono::high_resolution_clock::now();
			m_counting = true;
		}
	}
	//Implemented by Daniel 03.07 10:29 AM
	bool GameTimer::timeOut()
	{
		bool timeout = false;
		m_end= std::chrono::high_resolution_clock::now();
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
