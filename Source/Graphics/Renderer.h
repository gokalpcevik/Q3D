#pragma once
#include <SDL2/SDL.h>
#include <cstdint>

namespace Q3D
{
	class Window;

	struct Rectangle
	{
		uint32_t x, y, width, height, color;
	};

	class Renderer
	{
	public:
		Renderer(Window* pWindow, uint32_t flags);
		Renderer(Renderer&) = delete;
		virtual ~Renderer();
		[[nodiscard]] auto IsNull() const -> bool;
		[[nodiscard]] auto GetSDLRenderer() const -> SDL_Renderer*;
		void Clear(uint8_t R, uint8_t G, uint8_t B, uint8_t A) const;
		void ClearColorBuffer(uint32_t color) const;
		void UpdateColorBuffer() const;
		void CopyColorBuffer() const;
		void Present() const;
		void SetPixel(uint32_t color, uint32_t index) const;
		void DrawRectangle(const Rectangle& rect) const;
	private:
		Window* m_Window{nullptr};
		SDL_Renderer* m_Renderer{nullptr};
		//It might be a better idea to use a std::vector here.
		uint32_t* m_ColorBuffer{nullptr};
		SDL_Texture* m_ColorBufferTexture{nullptr};

		uint32_t m_WindowWidth = 1280;
		uint32_t m_WindowHeight = 720;

		friend class Window;
	};
}
