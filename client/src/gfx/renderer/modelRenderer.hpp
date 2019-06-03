#pragma once

#include <vector>
#include "../shaders/defaultShader.hpp"
#include "../model.hpp"
#include "../camera.hpp"

class ModelRenderer
{

public:
	ModelRenderer();	
	
	void addModel(Model &model);
	void removeModel(Model &model);
	void render(Camera &cam);

private:
	DefaultShader m_shader;	
	std::vector<Model> m_models;
	void renderModel(Model &model);
};

