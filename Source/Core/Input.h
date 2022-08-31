#pragma once
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <Eigen/Eigen>

namespace Q3D
{
	namespace Core
	{
		using Eigen::Vector2i;

		class Input
		{
		public:
			Input() = default;
			Input(const Input&) = delete;

			static bool IsKeyPressed(SDL_Scancode key);
			static bool IsLeftMouseButtonPressed();
			static bool IsRightMouseButtonPressed();
			static Vector2i GetCursorPosition();
		private:

		};
	}
}