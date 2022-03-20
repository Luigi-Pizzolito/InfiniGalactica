#pragma once
#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Control {
	class Timer {
	protected:
		std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
		std::chrono::duration<float> m_duration;

		Timer();
		virtual ~Timer();
	};
	class GameTimer :public Timer {
	private:
		float m_cycleduration;
		bool m_counting;
	public:
		GameTimer();
		GameTimer(float duration);
		~GameTimer();
		void setDuration(float duration);
		float getDuration() { return m_cycleduration; }
		void start();
		bool timeOut();
	};

}

namespace Debug
{
	class AutomaticTimer :public Control::Timer {
	public:

		AutomaticTimer();
		~AutomaticTimer();
	};
	class ManualTimer :public Control::Timer {
	public:
		ManualTimer();
		~ManualTimer();
		void start();
		void stop();

	};



	class XAxis {
		private:
			sf::RenderWindow* m_window;
			const sf::View* c_view;
			sf::VertexArray* lines;
			sf::Vector2f* total_length;
			bool ready = false;
		public:
			XAxis(sf::RenderWindow* window, const sf::View* view, sf::Vector2f* total_length);
			~XAxis();
			void draw();
	};
};
