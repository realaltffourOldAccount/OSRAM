#pragma once
#include <iostream>
#include <chrono>

namespace OSRAM
{
	namespace UTILS
	{
		struct Timer
		{
			std::chrono::time_point<std::chrono::steady_clock> _start, _end, _getVal;
			std::chrono::duration<float> duration;

			void Start()
			{
				_start = std::chrono::high_resolution_clock::now();
			}

			float get()
			{
				std::chrono::duration<float> duration;
				_getVal = std::chrono::high_resolution_clock::now();
				duration = _getVal - _start;

				float ms = duration.count() * 1000;
				return ms;
			}

			~Timer()
			{
				_end = std::chrono::high_resolution_clock::now();
				duration = _end - _start;

				float ms = duration.count() * 1000;
				std::cout << "[TIMER] Timer Destruct at: " << ms << "ms" << std::endl;
			}
			void Terminate()
			{
				_end = std::chrono::high_resolution_clock::now();
				duration = _end - _start;

				float ms = duration.count() * 1000;
				std::cout << ms << "ms" << std::endl;
			}
		};
	}
}