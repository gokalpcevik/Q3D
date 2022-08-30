#pragma once
#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <vector>
#include "Log.h"
#include "Window.h"
#include "../Math/VectorTransform.h"
#include "../AssetCore/MeshLibrary.h"
#include "../ECS/Scene.h"
#include "../ECS/Entity.h"
#include "../Utility/Random.h"

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

		using Eigen::Vector4f;
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

		private:
			AppStats m_Stats{};
			bool m_Running = true;
			std::unique_ptr<Window> m_Window;
			uint32_t m_WindowW = 1920U;
			uint32_t m_WindowH = 1080U;

			std::vector<Graphics::Vertex> m_MeshVertices{};
			std::vector<Graphics::Face> m_MeshFaces{};

			std::unique_ptr<ECS::Scene> m_MainScene;
			ECS::Entity m_Sphere;
			ECS::Entity m_Cube;
		};
	}
}
