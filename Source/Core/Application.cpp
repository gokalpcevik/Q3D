#include "Application.h"

namespace Q3D
{
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
		m_WindowH = disp.h;
		m_WindowW = disp.w;
		m_Window = std::make_unique<Window>(
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			disp.w,
			disp.h,
			"Q3D Graphics",
			SDL_WINDOW_FULLSCREEN_DESKTOP
		);
		if (m_Window->IsNull())
			return 0;

		if (!m_Window->CreateRenderer(0))
			return 0;

		{
			size_t iPoint = 0;
			for (float x = -1.0f; x <= 1.0f; x += 0.25f)
				for (float y = -1.0f; y <= 1.0f; y += 0.25f)
					for (float z = -1.0f; z <= 1.0f; z += 0.25f)
						m_PointCloud[iPoint++] = Vector3f(x, y, z);
		}


		return Update();
	}

	auto Application::Update() -> int32_t
	{
		while (m_Running)
		{
			auto counter = SDL_GetPerformanceCounter();
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
						else if (m_Window->GetEvent().key.keysym.sym == SDLK_F1)
						{
							Q3D_INFO("FPS: {0:.2f}", m_Stats.GetFramesPerSecond());
						}
					}
				}
			}
			Transform_Project();



			GetRenderer()->ClearColorBuffer_Black();
			//-------------------------------------------------
			RenderPoints();
			//-------------------------------------------------
			GetRenderer()->UpdateColorBuffer();
			GetRenderer()->CopyColorBuffer();
			GetRenderer()->Present();
		}
		GetRenderer()->Shutdown();
		SDL_Quit();
		return 0;
	}

	void Application::Transform_Project()
	{
		for (size_t i = 0; i < POINT_COUNT; i++)
		{
			auto v = m_PointCloud[i];
			
			static float rot = 0.0f;
			rot += 0.000005f;
			v = Math::RotateY(v, rot);
			v = Math::RotateZ(v, rot);
			v = Math::RotateX(v, rot);
			// Move the camera 3.0 points behind so we can see our points but more importantly,
			// avoid division by 0.0f which we do not handle at the moment
			v[2] -= 3.0f;
			m_ProjectedPoints[i] = Renderer::Project(v);
		}
	}

	void Application::RenderPoints()
	{
		std::for_each(m_ProjectedPoints.begin()
			, m_ProjectedPoints.end()
			, [&](Vector2f v) 
			{ Rectangle rect{ (uint32_t)v[0] + m_WindowW / 2,(uint32_t)v[1] + m_WindowH / 2,6,6,0xFFFFFF0F };
		GetRenderer()->DrawRectangle(rect); });
	}
}
