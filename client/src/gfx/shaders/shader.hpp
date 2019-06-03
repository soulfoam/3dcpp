#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{

public:
	Shader(const std::string &vertPath, const std::string &fragPath);
	~Shader();
	
	GLuint getGlId() { return m_glId; }
	void use() { glUseProgram(m_glId); }

	void addVertDefine(const std::string &def);
	void addFragDefine(const std::string &def);	
	void compile();


private:
	GLuint m_glId;
	std::string m_vertSrc;
	std::string m_fragSrc;

protected:
	GLint getUniformLocation(const std::string &name);
	void bindAttribute(GLuint attribute, const std::string &name);
	void loadBool(GLuint &loc, bool &b);
	void loadFloat(GLuint &loc, float &f);
	void loadVec3(GLuint &loc, const glm::vec3 &v);
	void loadMat4(GLuint &loc, const glm::mat4 &m);
};
