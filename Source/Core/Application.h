#pragma once
#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <vector>
#include "Log.h"
#include "Window.h"
#include "../Math/VectorTransform.h"

namespace Q3D
{
	using Eigen::Vector3f;
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

	static constexpr size_t CLOUD_DIM = 9;
	static constexpr size_t POINT_COUNT = CLOUD_DIM * CLOUD_DIM * CLOUD_DIM;

	class Application
	{
	public:
		Application() = default;
		static auto Get() -> Application&;
		auto Start() -> int32_t;
	private:
		auto Update() -> int32_t;
		auto GetRenderer() const -> const std::unique_ptr<Renderer>& { return m_Window->GetRenderer(); }

		// Transforms the points and projects them.
		void Transform_Project(float ts);
		// Renders/draws the projected points.
		void RenderPoints() const;
	private:
		AppStats m_Stats{};
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		std::array<Vector3f, POINT_COUNT> m_PointCloud = {};
		std::array<Vector2f,POINT_COUNT> m_ProjectedPoints = {};
		uint32_t m_WindowW = 1920;
		uint32_t m_WindowH = 1080;
	};
}
