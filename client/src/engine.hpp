#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "gfx/display.hpp"
#include "gfx/renderer/masterRenderer.hpp"

class Engine
{

public:
	Engine();
	~Engine();

	void start();
	void loop();
	void tick(bool fixedTick);
	void render();
	void events();

private:
	bool m_quit;
	float m_tickRate;
	float m_deltaTime;
	float m_renderTime;

	MasterRenderer m_masterRenderer;

};

