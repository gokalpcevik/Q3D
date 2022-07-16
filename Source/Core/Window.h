#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <string_view>
#include "Log.h"
#include "../Graphics/Renderer.h"

namespace Q3D
{
	class Window
	{
	public:
		Window(uint32_t w, uint32_t h, std::string_view title);
		Window(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string_view title, uint32_t flags);
		Window(const Window&) = delete;
		virtual ~Window();
		auto PollEvents() -> int;
		[[nodiscard]] auto GetEvent() const -> const SDL_Event& { return m_Event; }
		[[nodiscard]] auto GetSDLWindow() const -> SDL_Window* { return m_Window; }
		[[nodiscard]] auto IsNull() const -> bool;
		[[nodiscard]] auto GetWidth() const -> uint32_t;
		[[nodiscard]] auto GetSurfaceWidth() const -> uint32_t;
		[[nodiscard]] auto GetHeight() const -> uint32_t;
		[[nodiscard]] auto GetSurfaceHeight() const -> uint32_t;
		[[nodiscard]] auto GetWin32WindowHandle() const -> HWND;
		auto CreateRenderer(uint32_t flags) -> bool;
		[[nodiscard]] auto GetRenderer() const -> const std::unique_ptr<Renderer>&;

		void SetTitle(const char* title) const;

	private:
		SDL_Window* m_Window = nullptr;
		SDL_Event m_Event{};
		std::unique_ptr<Renderer> m_Renderer;
	};
}
