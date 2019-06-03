#include "model.hpp"

Model::Model(Mesh &mesh, glm::vec3 pos)
: 
m_drawable(mesh), 
m_position(pos), 
m_rotation(glm::vec3(0, 0, 0)), 
m_scale(glm::vec3(1, 1, 1)),
m_modelMatrix(glm::mat4(1)) 
{

}
