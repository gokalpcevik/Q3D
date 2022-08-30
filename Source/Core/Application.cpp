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
			m_WindowW = 640;
			m_WindowH = 480;
			m_Window = std::make_unique<Window>(
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				m_WindowW,
				m_WindowH,
				"Software Renderer",
				0
				);
			if (m_Window->IsNull())
				return 0;
			if (!m_Window->CreateRenderer(0))
				return 0;

			m_MainScene = std::make_unique<ECS::Scene>();

			auto& [id, data] = AssetCore::MeshLibrary::Load("Assets/sphere.obj");
			m_Sphere = m_MainScene->CreateEntity();
			m_Sphere.GetComponent<ECS::TransformComponent>().Translation = {0.0f,0.0f,4.5f,0.0f };
			auto& mc = m_Sphere.AddComponent<ECS::MeshComponent>();
			mc.MeshAssetId = id;
			mc.Color = 0xFF0F00FF;
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
						}
						if (m_Window->GetEvent().key.keysym.sym == SDLK_F2)
						{
							switch (GetRenderer()->GetRenderMode())
							{
								case Graphics::RenderMode::FillAndWireframe:
								{
									GetRenderer()->SetRenderMode(Graphics::RenderMode::Fill);
									break;
								}

								case Graphics::RenderMode::Fill:
								{
									GetRenderer()->SetRenderMode(Graphics::RenderMode::Wireframe);
									break;
								}
								case Graphics::RenderMode::Wireframe:
								{
									GetRenderer()->SetRenderMode(Graphics::RenderMode::FillAndWireframe);
									break;
								}
							}
						}
						if (m_Window->GetEvent().key.keysym.sym == SDLK_F3)
						{
							switch (GetRenderer()->GetCullMode())
							{
								case Graphics::CullMode::CullBack:
								{
									GetRenderer()->SetCullMode(Graphics::CullMode::CullNone);
									break;
								}
								case Graphics::CullMode::CullNone:
								{
									GetRenderer()->SetCullMode(Graphics::CullMode::CullBack);
									break;
								}
							}
						}
						if (m_Window->GetEvent().key.keysym.sym == SDLK_F4)
						{
							GetRenderer()->ToggleNormalVisualization();
							break;
						}
					}
					}
				}
				GetRenderer()->ClearColorBuffer_Black();
				//-------------------------------------------------
				static float rot = 0.0f;
				rot += 0.0008f * m_Stats.GetFrameTime();
				if (rot >= 100.0f)
					rot = 0.0f;
				auto& tc = m_Sphere.GetComponent<ECS::TransformComponent>();
				tc.Rotation = { rot,rot,rot };

				m_MainScene->Draw(*GetRenderer());
				//-------------------------------------------------
				GetRenderer()->UpdateColorBuffer();
				GetRenderer()->CopyColorBuffer();
				GetRenderer()->Present();
			}
			GetRenderer()->Shutdown();
			SDL_Quit();
			return 0;
		}
	}
}
