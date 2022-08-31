#include "Input.h"

namespace Q3D
{
	namespace Core
	{
		bool Input::IsKeyPressed(SDL_Scancode key)
		{
			const Uint8* state = SDL_GetKeyboardState(NULL);
			return state[key];
		}

		bool Input::IsLeftMouseButtonPressed()
		{
			int64_t buttons = SDL_GetMouseState(NULL,NULL);
			return (buttons & SDL_BUTTON_LMASK) != 0;
		}

		bool Input::IsRightMouseButtonPressed()
		{
			int64_t buttons = SDL_GetMouseState(NULL,NULL);
			return (buttons & SDL_BUTTON_RMASK) != 0;
		}

		Vector2i Input::GetCursorPosition()
		{
			int x,y;
			SDL_GetMouseState(&x,&y);
			return Vector2i{x,y};
		}
	}
}