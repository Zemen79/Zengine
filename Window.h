#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include "Error.h"

namespace Zen {
	class Window
	{
	public:
		Window();
		~Window();

		void Create(std::string title, int screenWidth, int screenHeight, bool fullScreen = false);
		void SwapBuffers();

		void HideCursor() { SDL_ShowCursor(SDL_DISABLE); }
		void ShowCursor() { SDL_ShowCursor(SDL_ENABLE); }

		void WrapCursorInsideWindow(SDL_bool enabled) { SDL_SetRelativeMouseMode(enabled); }

	private:
		SDL_Window* m_window;
	};
}