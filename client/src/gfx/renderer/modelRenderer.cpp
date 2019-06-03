#include <algorithm>
#include <glm/gtx/string_cast.hpp> 
#include "modelRenderer.hpp"

ModelRenderer::ModelRenderer()
{
	MeshBundle mb("res/models/debug.mb");
	m_models.emplace_back(mb.getMesh("terrain"), glm::vec3(0, 0, 0));
}

static void
mat4Print(glm::mat4 &m)
{
	for (int row = 0; row < 4; row++)
	{
		printf("\n");
		for (int col = 0; col < 4; col++)
		{
			if (fabs(m[col][row]) <= 0.0001) 
			{	
				printf("  .  \t");
			}
			else
			{
				printf("% 3.2f\t", m[col][row]);
			}
		}
	}

}

void
ModelRenderer::addModel(Model &model)
{
	m_models.push_back(model);	
}

void
ModelRenderer::removeModel(Model &model)
{
	//std::remove(m_models.begin(), m_models.end(), model);
}

void
ModelRenderer::renderModel(Model &model)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	m_shader.loadModelMatrix(modelMatrix);

	glBindVertexArray(model.getDrawable().getVao());
	glDrawElements(GL_TRIANGLES, model.getDrawable().getIndiceCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void
ModelRenderer::render(Camera &cam)
{
	m_shader.use();

	glm::mat4 viewMatrix = cam.getViewMatrix();
	m_shader.loadViewMatrix(viewMatrix);

	glm::mat4 projectionMatrix = cam.getProjectionMatrix();
	m_shader.loadProjectionMatrix(projectionMatrix);

	for (auto &e : m_models)
	{
		renderModel(e);	
	}
}

