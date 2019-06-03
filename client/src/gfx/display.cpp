#include <GL/glew.h>
#include "display.hpp"

static void 
setAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

Display::Display(const std::string &title, glm::ivec2 windowSize)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL" << std::endl;
		return;
	}

	m_window = SDL_CreateWindow(title.c_str(), 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			windowSize.x, windowSize.y, 
			SDL_WINDOW_OPENGL);

	if (!m_window)
	{
		std::cout << "Failed to init window" << std::endl;
		return;
	}

	m_context = SDL_GL_CreateContext(m_window);	

	if (!m_context)
	{
		std::cout << "Failed to create GL Context" << std::endl;
		return;
	}

	glewExperimental = true;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return;
	}

//Vsync has a bug with emscripten
#ifndef __EMSCRIPTEN__
	SDL_GL_SetSwapInterval(1);
#endif
	
	setAttributes();
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

glm::ivec2
Display::getWindowSize()
{
	glm::ivec2 size;
	SDL_GetWindowSize(m_window, &size.x, &size.y);
	return size;
}

float
Display::getWindowAspect()
{
	glm::ivec2 windowSize = getWindowSize();
	return (float)windowSize.x / (float)windowSize.y;
}

