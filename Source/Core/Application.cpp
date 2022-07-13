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

		m_Window = std::make_shared<Window>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1280, 720, "Q3D", 0);
		return Update();
	}

	auto Application::Update() -> int32_t
	{
		while (m_Running)
		{
			while(m_Window->PollEvents())
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
						Q3D_INFO("Window resized to {0}x{1}", m_Window->GetEvent().window.data1, m_Window->GetEvent().window.data2);
						break;
					}
					default: break;
					}
				}
				default: break;
				}
			}
		}
		return 0;
	}
}
