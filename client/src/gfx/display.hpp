#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

class Display
{

public:

	Display(const std::string &title, glm::ivec2 windowSize);
	~Display();

	SDL_Window *getWindow() { return m_window; }
	glm::ivec2 getWindowSize();
	float getWindowAspect();

private:
	SDL_Window *m_window;
	SDL_GLContext m_context;
};

