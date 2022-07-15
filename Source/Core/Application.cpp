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
		SDL_DisplayMode displayMode{};
		SDL_GetCurrentDisplayMode(0, &displayMode);
		m_Window = std::make_unique<Window>(
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800,
			600,
			"Q3D Graphics",
			0
		);

		if (m_Window->IsNull())
			return 0;

		if (!m_Window->CreateRenderer(0))
			return 0;

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
			GetRenderer()->Clear(125, 255, 255, 255);
			GetRenderer()->ClearColorBuffer_Black();
			Rectangle rect{ 50,50,100,100,0xFF00FFFF };
			GetRenderer()->DrawRectangle(rect);
			GetRenderer()->UpdateColorBuffer();
			GetRenderer()->CopyColorBuffer();
			GetRenderer()->Present();
			
		}
		GetRenderer()->Shutdown();
		SDL_Quit();
		return 0;
	}
}
