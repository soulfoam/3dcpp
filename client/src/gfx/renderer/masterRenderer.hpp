#pragma once

#include "modelRenderer.hpp"
#include "../camera.hpp"
#include "../display.hpp"

class MasterRenderer
{

public:
	MasterRenderer();
	
	Display &getDisplay() { return m_display; }
	Camera &getCamera() { return m_camera; }
	ModelRenderer &getModelRenderer() { return m_modelRenderer; }

	void render();

private:
	Display m_display;
	Camera m_camera;
	ModelRenderer m_modelRenderer;

};

