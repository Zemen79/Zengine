#include "Window.h"

namespace Zen {
	Window::Window() :
		m_window(nullptr)
	{
	}

	Window::~Window()
	{
	}

	void Window::Create(std::string title, int screenWidth, int screenHeight, bool fullScreen)
	{
		// initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// open an SDL window
		if (fullScreen)
			m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
		else
			m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (m_window == nullptr)
		{
			Error("SDL Window could not be created.");
		}

		// setup opengl context
		SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
		if (glContext == nullptr)
		{
			Error("SDL_GL context could not be created.");
		}

		// setup glew (optional but recommended)
		glewExperimental = true;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			Error("Glew could not be initialized.");
		}

		// Check opengl version
		std::printf("*** OPENGL VERSION: %s ***\n\n", glGetString(GL_VERSION));

		// set viewport
		glViewport(0, 0, screenWidth, screenHeight);

		// set the background color to red
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);

		// tell opengl we need doublebuffering so we dont get any fleekering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Alpha blendin/ transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// 0 = unlimited, 1 = vsync, 2 = adaptive vsync
		SDL_GL_SetSwapInterval(0);
	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_window);
	}
}