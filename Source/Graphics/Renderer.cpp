#include "Renderer.h"
#include "../Core/Window.h"

namespace Q3D
{
	namespace Graphics
	{
		uint32_t Color_RGBA(uint8_t A, uint8_t R, uint8_t G, uint8_t B)
		{
			return ((uint32_t)A << 24) | ((uint32_t)R << 16) | ((uint32_t)G << 8) | (uint32_t)B;
		}

		Renderer::Renderer(Core::Window *pWindow, uint32_t flags)
			: m_Window(pWindow), m_Renderer(SDL_CreateRenderer(pWindow->GetSDLWindow(), -1, flags))
		{
			if (!m_Renderer)
			{
				Q3D_ERROR("Something has gone wrong while creating the SDL window. Error Message:\n {0}", SDL_GetError());
				return;
			}
			m_WindowHeight = pWindow->GetHeight();
			m_WindowWidth = pWindow->GetWidth();
			// Color Format ARGB
			m_ColorBuffer = new uint32_t[m_WindowWidth * m_WindowHeight];
			std::uninitialized_fill_n(m_ColorBuffer, m_WindowWidth * m_WindowHeight, 0xFF000000);
			m_ColorBufferTexture = SDL_CreateTexture(m_Renderer,
													 SDL_PIXELFORMAT_ARGB8888,
													 SDL_TEXTUREACCESS_STREAMING,
													 m_WindowWidth,
													 m_WindowHeight);
			m_RenderList.reserve(4096);
		}

		auto Renderer::IsNull() const -> bool
		{
			return !m_Renderer;
		}

		void Renderer::Clear(uint8_t R, uint8_t G, uint8_t B, uint8_t A) const
		{
			// TODO: Check for errors(0 on success, -1 on failure...)
			SDL_SetRenderDrawColor(m_Renderer, R, G, B, A);
			SDL_RenderClear(m_Renderer);
		}

		void Renderer::ClearColorBuffer(uint32_t color)
		{
			// This is a bit slow for debug builds but the compiler takes care of the optimization in the release build.
			// Also we could do this with a for loop(nested or not, also unroll it etc.) but the performance of the two is nearly the same both in debug
			// and release builds.
			std::fill_n(m_ColorBuffer, m_WindowWidth * m_WindowHeight, color);
			this->Internal_Mesh_RenderList_Clear();
		}

		void Renderer::ClearColorBuffer_Black()
		{
			std::memset(m_ColorBuffer, 0, GetColorBufferByteWidth());
			this->Internal_Mesh_RenderList_Clear();
		}
		void Renderer::UpdateColorBuffer()
		{
			this->Internal_Mesh_Draw();
			SDL_UpdateTexture(m_ColorBufferTexture,
							  nullptr,
							  m_ColorBuffer,
							  (m_WindowWidth * 4));
		}

		void Renderer::CopyColorBuffer()
		{
			SDL_RenderCopy(m_Renderer, m_ColorBufferTexture, nullptr, nullptr);
		}

		void Renderer::Present() const
		{
			SDL_RenderPresent(m_Renderer);
		}

		void Renderer::DrawPixel(uint32_t index, uint32_t color) const
		{
			if (GetColorBufferSize() <= index)
				return;
			m_ColorBuffer[index] = color;
		}

		void Renderer::DrawPixel(uint32_t x, uint32_t y, uint32_t color) const
		{
			if ((m_WindowWidth <= x) || (m_WindowHeight <= y))
				return;
			m_ColorBuffer[m_WindowWidth * y + x] = color;
		}

		void Renderer::DrawRectangle(const Rectangle &rect) const
		{
			if ((m_WindowWidth <= rect.x + rect.width) || (m_WindowHeight <= rect.y + rect.height))
				return;
			for (size_t y = rect.y; y < rect.y + rect.height; y++)
			{
				for (size_t x = rect.x; x < rect.x + rect.width; x++)
				{
					m_ColorBuffer[m_WindowWidth * y + x] = rect.color;
				}
			}
		}

		void Renderer::DrawTriangle(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const
		{
			DrawLine(v0[0], v0[1], v1[0], v1[1], color);
			DrawLine(v1[0], v1[1], v2[0], v2[1], color);
			DrawLine(v2[0], v2[1], v0[0], v0[1], color);
		}

		void Renderer::DrawTriangleFilled(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const
		{
			if (v0[1] > v1[1])
				v0.swap(v1);
			if (v1[1] > v2[1])
				v1.swap(v2);
			if (v0[1] > v1[1])
				v0.swap(v1);

			int32_t Mx = (int32_t)(((float)v1[1] - v0[1]) * ((float)v2[0] - v0[0]) / ((float)v2[1] - v0[1])) + v0[0];
			int32_t My = v1[1];
			FillFlatBottom(v0, v1, {Mx, My}, color);
			FillFlatTop(v1, {Mx, My}, v2, color);
		}

		void Renderer::FillFlatBottom(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const
		{
			float oneOverM1 = ((float)v1[0] - v0[0]) / ((float)v1[1] - v0[1]);
			float oneOverM2 = ((float)v2[0] - v0[0]) / ((float)v2[1] - v0[1]);

			float xStart = v0[0];
			float xEnd = v0[0];

			for (int32_t y = v0[1]; y <= v1[1]; ++y)
			{
				DrawLine((uint32_t)xStart, y, (uint32_t)xEnd, y, color);
				xStart += oneOverM1;
				xEnd += oneOverM2;
			}
		}

		void Renderer::FillFlatTop(Vector2i v0, Vector2i v1, Vector2i v2, uint32_t color) const
		{
			float oneOverM1 = ((float)v2[0] - v0[0]) / (float)(v2[1] - v0[1]);
			float oneOverM2 = ((float)v2[0] - v1[0]) / (float)(v2[1] - v1[1]);
			float xStart = (float)v2[0];
			float xEnd = (float)v2[0];
			for (int32_t y = v2[1]; y >= v1[1]; y--)
			{
				DrawLine((uint32_t)xStart, y, (uint32_t)xEnd, y, color);
				xStart -= oneOverM1;
				xEnd -= oneOverM2;
			}
		}

		void Renderer::DrawMesh(const Mesh &mesh, uint32_t color)
		{
			for (size_t i = 0; i < mesh.Faces.size(); ++i)
			{
				Face const &face = mesh.Faces[i];
				Vector3f v0 = mesh.Vertices[face.i0].Position;
				Vector3f v1 = mesh.Vertices[face.i1].Position;
				Vector3f v2 = mesh.Vertices[face.i2].Position;
				Vector3f vNormal = mesh.Vertices[face.i0].Normal;

				// Rotates use std::sinf and std::cosf so they are really expensive
				// so we should probably avoid them if they are 0

				if (mesh.Rotation[0] != 0.0f)
				{
					v0 = Math::RotateX(v0, mesh.Rotation[0]);
					v1 = Math::RotateX(v1, mesh.Rotation[0]);
					v2 = Math::RotateX(v2, mesh.Rotation[0]);
					vNormal = Math::RotateX(vNormal, mesh.Rotation[0]);
				}
				if (mesh.Rotation[1] != 0.0f)
				{
					v0 = Math::RotateY(v0, mesh.Rotation[1]);
					v1 = Math::RotateY(v1, mesh.Rotation[1]);
					v2 = Math::RotateY(v2, mesh.Rotation[1]);
					vNormal = Math::RotateY(vNormal, mesh.Rotation[1]);
				}
				if (mesh.Rotation[2] != 0.0f)
				{
					v0 = Math::RotateZ(v0, mesh.Rotation[2]);
					v1 = Math::RotateZ(v1, mesh.Rotation[2]);
					v2 = Math::RotateZ(v2, mesh.Rotation[2]);
					vNormal = Math::RotateZ(vNormal, mesh.Rotation[2]);
				}

				v0 += mesh.Translation;
				v1 += mesh.Translation;
				v2 += mesh.Translation;

				Vector3f cameraDirection = (m_CameraPosition - v0).normalized();

				switch (m_CullMode)
				{
				case CullMode::CullBack:
				{
					if (cameraDirection.dot(vNormal) <= 0.0f)
						continue;
				}
				case CullMode::CullNone:
					break;
				}

				Vector2f p0 = Project(v0);
				Vector2f p1 = Project(v1);
				Vector2f p2 = Project(v2);
				p0[0] += (float)m_WindowWidth / 2.0f;
				p0[1] += (float)m_WindowHeight / 2.0f;
				p1[0] += (float)m_WindowWidth / 2.0f;
				p1[1] += (float)m_WindowHeight / 2.0f;
				p2[0] += (float)m_WindowWidth / 2.0f;
				p2[1] += (float)m_WindowHeight / 2.0f;

				float averageDepth = (v0[2] + v1[2] + v2[2]) / 3.0f;
				m_RenderList.emplace_back(Triangle{{p0, p1, p2}, averageDepth, color});

				if (m_NormalVizEnabled)
				{
					Vector3f n0 = v0 + vNormal / 5.0f;

					Vector2f np0 = Project(n0);
					np0[0] += (float)m_WindowWidth / 2.0f;
					np0[1] += (float)m_WindowHeight / 2.0f;

					Vector2i npi0 = {std::lround(np0[0]), std::lround(np0[1])};

					DrawLine((uint32_t)p0[0], (uint32_t)p0[1], npi0[0], npi0[1], 0xFFFF00FF);
				}
			}
		}

		void Renderer::DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) const
		{
			int32_t dx = (x1 - x0);
			int32_t dy = (y1 - y0);

			uint32_t steps =
				std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);
			float Xinc = (float)dx / (float)steps;
			float Yinc = (float)dy / (float)steps;
			float x = (float)x0;
			float y = (float)y0;

			for (uint32_t i = 0; i <= steps; ++i)
			{
				DrawPixel(round(x), round(y), color);
				x += Xinc;
				y += Yinc;
			}
		}

		void Renderer::Internal_Mesh_Draw()
		{
			if(m_DepthSort == DepthSort::PaintersAlgorithm)
			{
				// Probably very expensive but no performance concerns for now
				std::sort(m_RenderList.begin(),m_RenderList.end(),[&](const Triangle& first,const Triangle& second){ return first.AverageDepth > second.AverageDepth;});
			}

			for (auto& triangle : m_RenderList)
			{
				Vector2i pi0 = {std::lround(triangle.Points[0][0]), std::lround(triangle.Points[0][1])};
				Vector2i pi1 = {std::lround(triangle.Points[1][0]), std::lround(triangle.Points[1][1])};
				Vector2i pi2 = {std::lround(triangle.Points[2][0]), std::lround(triangle.Points[2][1])};

				switch (m_RenderMode)
				{
				case RenderMode::FillAndWireframe:
				{
					DrawTriangleFilled(pi0, pi1, pi2, triangle.Color);
					DrawTriangle(pi0, pi1, pi2, 0xFFFFFFFF);
					break;
				}

				case RenderMode::Fill:
				{
					DrawTriangleFilled(pi0, pi1, pi2, triangle.Color);
					break;
				}
				case RenderMode::Wireframe:
				{
					DrawTriangle(pi0, pi1, pi2, 0xFFFFFFFF);
					break;
				}
				}
			}
		}

		void Renderer::Internal_Mesh_RenderList_Clear()
		{
			m_RenderList.clear();
			m_RenderList.reserve(4096);
		}

		void Renderer::SetCameraPosition(const Vector3f &pos)
		{
			m_CameraPosition = pos;
		}

		void Renderer::SetRenderMode(RenderMode rm)
		{
			m_RenderMode = rm;
		}

		void Renderer::SetCullMode(CullMode cm)
		{
			m_CullMode = cm;
		}

		void Renderer::SetDepthSortMode(DepthSort dsm)
		{
			m_DepthSort = dsm;
		}

		void Renderer::ToggleNormalVisualization()
		{
			m_NormalVizEnabled = !m_NormalVizEnabled;
		}

		void Renderer::Shutdown() const
		{
			delete[] m_ColorBuffer;
			SDL_DestroyTexture(m_ColorBufferTexture);
			SDL_DestroyRenderer(m_Renderer);
		}

		auto Renderer::GetRenderMode() const -> RenderMode
		{
			return m_RenderMode;
		}

		auto Renderer::GetCullMode() const -> CullMode
		{
			return m_CullMode;
		}

		auto Renderer::Project(const Vector3f &pos) -> Vector2f
		{
			// This is essentially a very hacky way of doing perspective
			return Vector2f{pos[0] * 640.0f / pos[2], pos[1] * 640.0f / pos[2]};
		}

		auto Renderer::GetSDLRenderer() const -> SDL_Renderer *
		{
			return m_Renderer;
		}

		auto Renderer::GetColorBuffer() const -> uint32_t *
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

		auto Renderer::GetColorBufferTexture() const -> SDL_Texture *
		{
			return m_ColorBufferTexture;
		}
	}
}
