#pragma once
#include <iostream>
#include <chrono>
#include <thread>
//Implemented by Daniel 03.07 10:00 AM
namespace Control {
	//Implemented by Daniel 03.07 10:01 AM
	class Timer {
	protected:
		std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
		std::chrono::duration<float> m_duration;

		Timer();
		virtual ~Timer();
	};
	//Implemented by Daniel 03.07 10:10 AM
	class DebugAutomaticTimer :public Timer {
	public:

		DebugAutomaticTimer();
		~DebugAutomaticTimer();
	};
	//Implemented by Daniel 03.07 10:20 AM
	class DebugManualTimer :public Timer {
	public:
		DebugManualTimer();
		~DebugManualTimer();
		void start();
		void stop();

	};
	//Implemented by Daniel 03.07 10:25 AM
	class GameTimer :public Timer {
	private:
		float m_cycleduration;
		bool m_counting;
	public:
		GameTimer();
		GameTimer(float duration);
		~GameTimer();
		void setDuration(float duration);
		void start();
		bool timeOut();
	};

}
