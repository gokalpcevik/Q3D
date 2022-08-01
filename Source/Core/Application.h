#pragma once
#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <vector>
#include "Log.h"
#include "Window.h"
#include "../Math/VectorTransform.h"

namespace Q3D
{
	namespace Core
	{
		struct AppStats
		{
			Uint64 m_LastTickCount = 0ULL;
			Uint64 m_FrameTime = 0ULL;

			[[nodiscard]] auto GetFramesPerSecond()		const -> float;
			[[nodiscard]] auto GetFrameTime()			const -> float;
			[[nodiscard]] auto GetFrameTimeSeconds()	const -> float;
		};


		using Eigen::Vector3f;
		using Eigen::Vector2f;
		using Eigen::Vector3i;
		class Application
		{
		public:
			Application() = default;
			static auto Get()->Application&;
			auto Start()->int32_t;
		private:
			auto Update()->int32_t;
			[[nodiscard]] auto GetRenderer() const -> const std::unique_ptr<Graphics::Renderer>& { return m_Window->GetRenderer(); }

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
			std::array<Graphics::Triangle, 6ULL * 2ULL> m_Triangles{};
		};
	}
}
