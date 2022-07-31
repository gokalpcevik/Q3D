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
	using Eigen::Vector3i;

	struct AppStats
	{
		Uint64 m_LastTickCount = 0U;
		Uint64 m_FrameTime = 0U;

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
		auto GetRenderer() const -> const std::unique_ptr<Renderer>& { return m_Window->GetRenderer(); }

		// Transforms the points and projects them.
		void Transform_Project(float ts);
		void DrawTriangles() const;
	private:
		AppStats m_Stats{};
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		uint32_t m_WindowW = 1920U;
		uint32_t m_WindowH = 1080U;

		std::array<Vector3f, 8ULL> m_MeshVertices{};
		std::array<Vector3i, 6ULL * 2ULL> m_MeshFaces{};
		std::array<Triangle, 6ULL * 2ULL> m_Triangles{};
	};
;}
