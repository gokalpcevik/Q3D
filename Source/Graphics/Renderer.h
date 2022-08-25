#pragma once
#include <SDL2/SDL.h>
#include <Eigen/Eigen>
#include <cstdint>
#include "Types.h"
#include "../Math/VectorTransform.h"

namespace Q3D
{
	namespace Core
	{
		class Window;
	}

	namespace Graphics
	{
		using Eigen::Vector3f;
		using Eigen::Vector2f;
		using Eigen::Vector2i;

		uint32_t Color_RGBA(uint8_t A,uint8_t R,uint8_t G,uint8_t B);

		enum class RenderMode : uint8_t
		{
			Fill = 0,
			Wireframe = 1,
			FillAndWireframe = 2
		};

		enum class CullMode : uint8_t
		{
			CullNone = 0,
			CullBack = 1
		};

		enum class DepthSort : uint8_t
		{
			None = 0,
			PaintersAlgorithm
		};

		class Renderer
		{
		public:
			Renderer(Core::Window* pWindow, uint32_t flags);
			Renderer(Renderer&) = delete;
			virtual ~Renderer() = default;
			[[nodiscard]] auto IsNull() const -> bool;
			[[nodiscard]] auto GetSDLRenderer() const->SDL_Renderer*;
			[[nodiscard]] auto GetColorBuffer() const->uint32_t*;
			[[nodiscard]] auto GetColorBufferSize() const->size_t;
			[[nodiscard]] auto GetColorBufferByteWidth() const->size_t;
			[[nodiscard]] auto GetColorBufferTexture() const->SDL_Texture*;
			void Clear(uint8_t R, uint8_t G, uint8_t B, uint8_t A) const;
			void ClearColorBuffer(uint32_t color);
			// This sets the entire color buffer to zero(black) and is significantly faster
			// than setting a specific color value.
			void ClearColorBuffer_Black();
			void UpdateColorBuffer();
			void CopyColorBuffer();
			void Present() const;
			void DrawPixel(uint32_t index, uint32_t color) const;
			void DrawPixel(uint32_t x, uint32_t y, uint32_t color) const;
			void DrawRectangle(const Rectangle& rect) const;
			void DrawTriangle(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const;
			void DrawTriangle(const Triangle& triangle, uint32_t color) const;
			void DrawTriangleFilled(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const;
			void FillFlatBottom(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const;
			void FillFlatTop(Vector2i v0, Vector2i v1, Vector2i v2,uint32_t color) const;
			void DrawMesh(const Mesh& mesh,uint32_t color);
			void DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) const;
			void SetCameraPosition(const Vector3f& pos);
			void SetRenderMode(RenderMode rm);
			void SetCullMode(CullMode cm);
			void SetDepthSortMode(DepthSort dsm);
			void ToggleNormalVisualization();
			void Shutdown() const;

			auto GetRenderMode() const->RenderMode;
			auto GetCullMode() const->CullMode;

			static auto Project(const Vector3f& pos)->Vector2f;
		private:
			void Internal_Mesh_Draw();
			void Internal_Mesh_RenderList_Clear();

		private:
			Core::Window* m_Window{ nullptr };
			SDL_Renderer* m_Renderer{ nullptr };
			uint32_t* m_ColorBuffer{ nullptr };
			SDL_Texture* m_ColorBufferTexture{ nullptr };

			uint32_t m_WindowWidth = 1920U;
			uint32_t m_WindowHeight = 1080U;

			Vector3f m_CameraPosition = { 0.0f,0.0f,0.0f };

			RenderMode m_RenderMode{ RenderMode::FillAndWireframe };
			CullMode m_CullMode{ CullMode::CullBack };
			DepthSort m_DepthSort { DepthSort::PaintersAlgorithm };

			bool m_NormalVizEnabled = false;

			std::vector<Triangle> m_RenderList{};
			friend class Window;
		};
	}
}
