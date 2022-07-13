#pragma once
#include <SDL2/SDL.h>
#include "Log.h"
#include "Window.h"

namespace Q3D
{
	struct AppStats
	{
		Uint64 m_LastTickCount = 0;
		Uint64 m_FrameTime = 0;

		auto GetFramesPerSecond() const -> float
		{
			return 1.0f / ((float)m_FrameTime / (float)SDL_GetPerformanceFrequency());
		}

		auto GetFrameTime() const -> float
		{
			return (float)m_FrameTime / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		}

		auto GetFrameTimeSeconds() const -> float
		{
			return (float)m_FrameTime / (float)SDL_GetPerformanceCounter();
		}
	};

	class Application
	{
	public:
		Application() = default;
		static auto Get() -> Application&;
		auto Start() -> int32_t;
	private:
		auto Update() -> int32_t;

	private:
		AppStats m_Stats{};
		bool m_Running = true;
		std::shared_ptr<Window> m_Window;
	};
}
