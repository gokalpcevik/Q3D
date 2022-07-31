#pragma once
#include <SDL2/SDL.h>
#include <Eigen/Eigen>
#include <cstdint>

namespace Q3D
{
	class Window;
	using Eigen::Vector3f;
	using Eigen::Vector2f;

	struct Rectangle
	{
		uint32_t x, y, width, height, color;
	};

	struct Triangle
	{
		std::array<Vector2f, 3ULL> points{};
	};

	class Renderer
	{
	public:
		Renderer(Window* pWindow, uint32_t flags);
		Renderer(Renderer&) = delete;
		virtual ~Renderer() = default;
		[[nodiscard]] auto IsNull() const -> bool;
		[[nodiscard]] auto GetSDLRenderer() const->SDL_Renderer*;
		[[nodiscard]] auto GetColorBuffer() const->uint32_t*;
		[[nodiscard]] auto GetColorBufferSize() const -> size_t;
		[[nodiscard]] auto GetColorBufferByteWidth() const -> size_t;
		[[nodiscard]] auto GetColorBufferTexture() const -> SDL_Texture*;
		void Clear(uint8_t R, uint8_t G, uint8_t B, uint8_t A) const;
		void ClearColorBuffer(uint32_t color) const;
		// This sets the entire color buffer to zero(black) and is significantly faster
		// than setting a specific color value.
		void ClearColorBuffer_Black() const;
		void UpdateColorBuffer() const;
		void CopyColorBuffer() const;
		void Present() const;
		void DrawPixel(uint32_t index,uint32_t color) const;
		void DrawPixel(uint32_t x,uint32_t y, uint32_t color) const;
		void DrawRectangle(const Rectangle& rect) const;
		void DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1,uint32_t color) const;
		void Shutdown() const;

		static auto Project(const Vector3f& pos) -> Vector2f;
	private:
		Window* m_Window{nullptr};
		SDL_Renderer* m_Renderer{nullptr};
		uint32_t* m_ColorBuffer{nullptr};
		SDL_Texture* m_ColorBufferTexture{nullptr};

		uint32_t m_WindowWidth = 1920;
		uint32_t m_WindowHeight = 1080;
		
		friend class Window;
	};
}
