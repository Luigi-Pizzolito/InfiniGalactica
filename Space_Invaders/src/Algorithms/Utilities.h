#pragma once
#include <iostream>
#include <chrono>
#include <thread>
namespace Control {
	class Timer {
	protected:
		std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
		std::chrono::duration<float> m_duration;

		Timer();
		virtual ~Timer();
	};
	class DebugAutomaticTimer :public Timer {
	public:

		DebugAutomaticTimer();
		~DebugAutomaticTimer();
	};
	class DebugManualTimer :public Timer {
	public:
		DebugManualTimer();
		~DebugManualTimer();
		void start();
		void stop();

	};
	class GameTimer :public Timer {
	private:
		float m_cycleduration;
		bool m_counting;
	public:
		GameTimer(float duration);
		~GameTimer();
		void start();
		bool timeOut();
	};

}