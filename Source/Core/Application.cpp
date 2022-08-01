#include "Application.h"

namespace Q3D
{
	namespace Core
	{
		auto AppStats::GetFramesPerSecond() const -> float
		{
			return 1.0f / ((float)m_FrameTime / (float)SDL_GetPerformanceFrequency());
		}

		auto AppStats::GetFrameTime() const -> float
		{
			return (float)m_FrameTime / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		}

		auto AppStats::GetFrameTimeSeconds() const -> float
		{
			return (float)m_FrameTime / (float)SDL_GetPerformanceCounter();
		}

		auto Application::Get() -> Application&
		{
			static Application instance;
			return instance;
		}

		auto Application::Start() -> int32_t
		{
			Log::Init();
			SDL_DisplayMode disp{};
			SDL_GetDisplayMode(0, 0, &disp);
			m_WindowW = 1600U;
			m_WindowH = 900U;
			m_Window = std::make_unique<Window>(
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				m_WindowW,
				m_WindowH,
				"Q3D Graphics",
				0
				);
			if (m_Window->IsNull())
				return 0;
			if (!m_Window->CreateRenderer(SDL_RENDERER_PRESENTVSYNC))
				return 0;


			m_MeshVertices =
			{
				Vector3f{-1.0f, -1.0f, -1.0f},
				Vector3f{-1.0f, 1.0f, -1.0f},
				Vector3f{1.0f, 1.0f, -1.0f},
				Vector3f{1.0f, -1.0f, -1.0f},
				Vector3f{1.0f, 1.0f, 1.0f},
				Vector3f{1.0f, -1.0f, 1.0f},
				Vector3f{-1.0f, 1.0f, 1.0f},
				Vector3f{-1.0f, -1.0f, 1.0f}
			};

			m_MeshFaces =
			{
				Vector3i{1, 2, 3},
				Vector3i{1, 3, 4},
				Vector3i{4, 3, 5},
				Vector3i{4, 5, 6},
				Vector3i{6, 5, 7},
				Vector3i{6, 7, 8},
				Vector3i{8, 7, 2},
				Vector3i{8, 2, 1},
				Vector3i{2, 7, 5},
				Vector3i{2, 5, 3},
				Vector3i{6, 8, 1},
				Vector3i{6, 1, 4}
			};
			return Update();
		}

		auto Application::Update() -> int32_t
		{
			while (m_Running)
			{
				auto const counter = SDL_GetPerformanceCounter();
				m_Stats.m_FrameTime = counter - m_Stats.m_LastTickCount;
				m_Stats.m_LastTickCount = counter;

				while (m_Window->PollEvents())
				{
					switch (m_Window->GetEvent().type)
					{
					case SDL_QUIT:
					{
						return 0;
					}
					case SDL_WINDOWEVENT:
					{
						switch (m_Window->GetEvent().window.event)
						{
						case SDL_WINDOWEVENT_RESIZED:
						{
							Q3D_INFO("Window resized to {0}x{1}", m_Window->GetEvent().window.data1,
								m_Window->GetEvent().window.data2);
							break;
						}
						default: break;
						}
					}
					case SDL_KEYDOWN:
					{
						if (m_Window->GetEvent().key.keysym.sym == SDLK_ESCAPE)
						{
							m_Running = false;
							break;
						}
						if (m_Window->GetEvent().key.keysym.sym == SDLK_F1)
						{
							Q3D_INFO("FPS: {0:.2f}", m_Stats.GetFramesPerSecond());
							Q3D_INFO("Frame Time: {0:.2f}ms", m_Stats.GetFrameTime());
							break;
						}
					}
					}
				}
				GetRenderer()->ClearColorBuffer_Black();
				//-------------------------------------------------
				Transform_Project(m_Stats.GetFrameTime());
				DrawTriangles();
				//-------------------------------------------------
				GetRenderer()->UpdateColorBuffer();
				GetRenderer()->CopyColorBuffer();
				GetRenderer()->Present();
			}
			GetRenderer()->Shutdown();
			SDL_Quit();
			return 0;
		}

		void Application::Transform_Project(float ts)
		{
			if (ts >= 10.0f)
				return;
			static float rot = 0.0f;
			rot += ts / 2000.0f;
			for (size_t i = 0; i < m_MeshFaces.size(); ++i)
			{
				Vector3i face = m_MeshFaces[i];

				std::array<Vector3f, 3ULL> faceVertices{};
				faceVertices[0] = m_MeshVertices[face[0] - 1];
				faceVertices[1] = m_MeshVertices[face[1] - 1];
				faceVertices[2] = m_MeshVertices[face[2] - 1];

				for (size_t j = 0; j < faceVertices.size(); ++j)
				{
					Vector3f v = faceVertices[j];
					v = Math::RotateY(v, rot);
					v = Math::RotateZ(v, rot);

					v[2] -= 4.0f;
					Eigen::Vector2f projected = Graphics::Renderer::Project(v);

					projected[0] += (float)m_WindowW / 2.0f;
					projected[1] += (float)m_WindowH / 2.0f;

					m_Triangles[i].points[j] = projected;
				}
			}
		}

		void Application::DrawTriangles() const
		{
			for (auto t : m_Triangles)
			{
				GetRenderer()->DrawLine(t.points[0][0], t.points[0][1], t.points[1][0], t.points[1][1], 0xFFFF0000);
				GetRenderer()->DrawLine(t.points[1][0], t.points[1][1], t.points[2][0], t.points[2][1], 0xFFFF0000);
				GetRenderer()->DrawLine(t.points[2][0], t.points[2][1], t.points[0][0], t.points[0][1], 0xFFFF0000);
			}
		}
	}
}
