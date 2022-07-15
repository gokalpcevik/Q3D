#include "Renderer.h"
#include "../Core/Window.h"

namespace Q3D
{
	Renderer::Renderer(Window* pWindow, uint32_t flags)
		: m_Window(pWindow), m_Renderer(SDL_CreateRenderer(pWindow->GetSDLWindow(), -1, flags))
	{
		if (!m_Renderer)
		{
			Q3D_ERROR("Something has gone wrong while creating the SDL window. Error Message:\n {0}", SDL_GetError());
			return;
		}
		m_WindowHeight = pWindow->GetHeight();
		m_WindowWidth = pWindow->GetWidth();
		//Color Format ARGB
		m_ColorBuffer = new uint32_t[m_WindowWidth * m_WindowHeight];
		std::uninitialized_fill_n(m_ColorBuffer, m_WindowWidth * m_WindowHeight, 0xFF000000);
		m_ColorBufferTexture = SDL_CreateTexture(m_Renderer,
		                                         SDL_PIXELFORMAT_ARGB8888,
		                                         SDL_TEXTUREACCESS_STREAMING,
		                                         m_WindowWidth,
		                                         m_WindowHeight);
	}

	auto Renderer::IsNull() const -> bool
	{
		return !m_Renderer;
	}

	void Renderer::Clear(uint8_t R, uint8_t G, uint8_t B, uint8_t A) const
	{
		//TODO: Check for errors(0 on success, -1 on failure...)
		SDL_SetRenderDrawColor(m_Renderer, R, G, B, A);
		SDL_RenderClear(m_Renderer);
	}

	void Renderer::ClearColorBuffer(uint32_t color) const
	{
		// This is a bit slow for debug builds but the compiler takes care of the optimization in the release build.
		// Also we could do this with a for loop(nested or not, also unroll it etc.) but the performance of the two is nearly the same both in debug
		// and release builds. 
		std::fill_n(m_ColorBuffer, m_WindowWidth * m_WindowHeight, color);
	}

	void Renderer::ClearColorBuffer_Black() const
	{
		std::memset(m_ColorBuffer, 0,GetColorBufferByteWidth());
	}

	void Renderer::UpdateColorBuffer() const
	{
		SDL_UpdateTexture(m_ColorBufferTexture,
		                  nullptr,
		                  m_ColorBuffer,
		                  (m_WindowWidth * 4));
	}

	void Renderer::CopyColorBuffer() const
	{
		SDL_RenderCopy(m_Renderer, m_ColorBufferTexture, nullptr, nullptr);
	}

	void Renderer::Present() const
	{
		SDL_RenderPresent(m_Renderer);
	}

	void Renderer::DrawPixel(uint32_t index, uint32_t color) const
	{
		m_ColorBuffer[index] = color;
	}

	void Renderer::DrawPixel(uint32_t x, uint32_t y, uint32_t color) const
	{
		m_ColorBuffer[m_WindowWidth * y + x] = color;
	}

	void Renderer::DrawRectangle(const Rectangle& rect) const
	{
		for(size_t y = rect.y; y < rect.y + rect.height; y++)
		{
			for (size_t x = rect.x; x < rect.x + rect.width; x++)
			{
				m_ColorBuffer[m_WindowWidth * y + x] = rect.color;
			}
		}
	}

	void Renderer::Shutdown() const
	{
		delete[] m_ColorBuffer;
		SDL_DestroyTexture(m_ColorBufferTexture);
		SDL_DestroyRenderer(m_Renderer);
	}

	auto Renderer::GetSDLRenderer() const -> SDL_Renderer*
	{
		return m_Renderer;
	}

	auto Renderer::GetColorBuffer() const -> uint32_t*
	{
		return m_ColorBuffer;
	}

	auto Renderer::GetColorBufferSize() const -> size_t
	{
		return (size_t)m_WindowHeight * m_WindowWidth;
	}

	auto Renderer::GetColorBufferByteWidth() const -> size_t
	{
		return (size_t)m_WindowHeight * m_WindowWidth * sizeof(uint32_t);
	}

	auto Renderer::GetColorBufferTexture() const -> SDL_Texture*
	{
		return m_ColorBufferTexture;
	}
}
