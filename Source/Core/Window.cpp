#include "Window.h"

namespace Q3D
{
	Window::Window(uint32_t w, uint32_t h, std::string_view title)
	{
		m_Window = SDL_CreateWindow(title.data(), 50, 50, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!m_Window)
		{
			Q3D_ERROR("Something has gone wrong while creating the SDL window. Error Message:\n {0}", SDL_GetError());
			return;
		}
	}

	Window::Window(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string_view title, uint32_t flags)
	{
		m_Window = SDL_CreateWindow(title.data(), x, y, w, h, flags);
		if (!m_Window)
		{
			Q3D_ERROR("Something has gone wrong while creating the SDL window. Error Message:\n {0}", SDL_GetError());
			return;
		}
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(m_Renderer->m_Renderer);
		SDL_DestroyWindow(m_Window);
	}

	auto Window::PollEvents() -> int
	{
		return SDL_PollEvent(&m_Event);
	}

	auto Window::GetWidth() const -> uint32_t
	{
		int w = 0;
		int h = 0;
		SDL_GetWindowSize(m_Window, &w, &h);
		return w;
	}

	auto Window::GetSurfaceWidth() const -> uint32_t
	{
		auto* surface = SDL_GetWindowSurface(m_Window);
		return surface->w;
	}

	auto Window::GetSurfaceHeight() const -> uint32_t
	{
		auto* surface = SDL_GetWindowSurface(m_Window);
		return surface->h;
	}

	auto Window::GetHeight() const -> uint32_t
	{
		int h = 0;
		int w = 0;
		SDL_GetWindowSize(m_Window, &w, &h);
		return h;
	}

	auto Window::GetWin32WindowHandle() const -> HWND
	{
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		SDL_GetWindowWMInfo(m_Window, &info);
		HWND hwnd = info.info.win.window;
		return hwnd;
	}

	auto Window::CreateRenderer(uint32_t flags) -> bool
	{
		m_Renderer = std::make_unique<Renderer>(this, flags);
		return !m_Renderer->IsNull();
	}

	auto Window::GetRenderer() const -> const std::unique_ptr<Renderer>&
	{
		return m_Renderer;
	}

	auto Window::IsNull() const -> bool
	{
		return m_Window == nullptr;
	}

	void Window::SetTitle(const char* title)
	{
		SDL_SetWindowTitle(m_Window, title);
	}
}
