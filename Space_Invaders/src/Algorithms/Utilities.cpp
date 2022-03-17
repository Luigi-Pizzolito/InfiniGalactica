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
	DebugAutomaticTimer::DebugAutomaticTimer()
	{
		m_start = std::chrono::steady_clock::now();
	}
	DebugAutomaticTimer::~DebugAutomaticTimer()
	{
		m_end = std::chrono::steady_clock::now();
		m_duration = m_end - m_start;
		float ms = m_duration.count() * 1000.0f;
		std::cout << "Time elapsed: " << ms << " ms" << "\n";
	}
	DebugManualTimer::DebugManualTimer()
	{

	}
	DebugManualTimer::~DebugManualTimer()
	{

	}
	void DebugManualTimer::start()
	{
		
		m_start = std::chrono::steady_clock::now();
	}
	void DebugManualTimer::stop()
	{
		m_end = std::chrono::steady_clock::now();
		m_duration = m_end - m_start;
		float ms = m_duration.count() * 1000.0f;
		std::cout << "Time elapsed: " << ms << " ms" << "\n";
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
