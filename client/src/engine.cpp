#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <chrono>
#include <thread>
#include <memory>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <core/ext/io.hpp>
#include "engine.hpp"
#include "gfx/display.hpp"
#include "gfx/meshBundle.hpp"
#include "gfx/shaders/shader.hpp"
#include "gfx/shaders/defaultShader.hpp"
#include "gfx/drawable.hpp"
#include "gfx/camera.hpp"

Engine::Engine()
:
m_quit(false),
m_tickRate(1000 / 25),
m_deltaTime(0),
m_renderTime(0)
{

}

Engine::~Engine()
{

}

void 
loopCallback(void *arg)
{
	static_cast<Engine*>(arg)->loop();
}

void 
Engine::start()
{
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(&loopCallback, this, 0, 1);
#else
	loop();
#endif
}

void 
Engine::events()
{
	//maybe have each module be notified
	//of events? that way the camera
	//can set its own aspect on resize
	
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				m_masterRenderer.getCamera().setAspect(
				m_masterRenderer.getDisplay().getWindowAspect());
			}
		}
		if (e.type == SDL_QUIT)
		{
			m_quit = true;
		}
	}
}

void 
Engine::tick(bool fixedTick)
{

}

void 
Engine::render()
{
	m_masterRenderer.render();
}

void 
Engine::loop()
{	
	double now          = SDL_GetTicks();
	double lastTime     = SDL_GetTicks();
	double accumulator  = 0;

	double displayTimer = 0;
	uint32_t ticks      = 0;
	uint32_t fps        = 0;

	while (!m_quit)
	{		
		now             = SDL_GetTicks();
		m_deltaTime     = now - lastTime;
		lastTime        = now;
		accumulator    += m_deltaTime;
		bool fixedTick  = false;

		displayTimer += m_deltaTime;
		
		events();
		
		while (accumulator >= m_tickRate)
		{
			tick(true);
			accumulator -= m_tickRate;
			fixedTick = true;
			ticks++;
		}

		if (!fixedTick)
		{
			tick(false);
		}
		
		m_renderTime = accumulator / m_tickRate;

		render();

		fps++;

		if (displayTimer > 1000)
		{
			std::cout << "Ticks: " << ticks << " FPS: " << fps << std::endl;
			ticks = 0;
			fps = 0;
			displayTimer = 0;
		}
		
	}
}
