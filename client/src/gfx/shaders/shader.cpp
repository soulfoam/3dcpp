#include <fstream>
#include <iostream>
#include "shader.hpp"

Shader::Shader(const std::string &vertPath, const std::string &fragPath)
{
	const std::string shadersPath = "res/shaders/";

	std::ifstream v(shadersPath + vertPath);
	if (!v.is_open())
	{
		std::cout << "Failed to open: " << vertPath << std::endl;
		return;
	}
	v.seekg(0, std::ios::end);   
	m_vertSrc.reserve(v.tellg());
	v.seekg(0, std::ios::beg);
	m_vertSrc.assign((std::istreambuf_iterator<char>(v)), std::istreambuf_iterator<char>());

	std::ifstream f(shadersPath + fragPath);
	if (!f.is_open())
	{
		std::cout << "Failed to open: " << fragPath << std::endl;
		return;
	}
	f.seekg(0, std::ios::end);   
	m_fragSrc.reserve(f.tellg());
	f.seekg(0, std::ios::beg);
	m_fragSrc.assign((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

Shader::~Shader()
{

}

void
Shader::addVertDefine(const std::string &def)
{
	m_vertSrc = def + "\n" + m_vertSrc;
}

void
Shader::addFragDefine(const std::string &def)
{
	m_fragSrc = def + "\n" + m_fragSrc;
}

static void
checkError(GLuint id, const std::string &type)
{
	GLint success;
	GLchar log[1024];
	if(type != "PROGRAM")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(id, 1024, NULL, log);
			std::cout << type << " Shader compile error " << log << std::endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(id, 1024, NULL, log);
			std::cout << type << " Shader linking error " << log << std::endl;
		}
	}

}

void
Shader::compile()
{

	m_vertSrc = "#version 330 core\n" + m_vertSrc;
	m_fragSrc = "#version 330 core\n" + m_fragSrc;

	GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
	const char *vSrc = m_vertSrc.c_str();
	glShaderSource(vertId, 1, &vSrc, NULL);
	glCompileShader(vertId);
	checkError(vertId, "VERTEX");

	GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fSrc = m_fragSrc.c_str();
	glShaderSource(fragId, 1, &fSrc, NULL);
	glCompileShader(fragId);
	checkError(fragId, "FRAGMENT");
	
	m_glId = glCreateProgram();
	glAttachShader(m_glId, vertId);
	glAttachShader(m_glId, fragId);

	glLinkProgram(m_glId);
	checkError(m_glId, "PROGRAM");

	glDeleteShader(vertId);
	glDeleteShader(fragId);
}

GLint
Shader::getUniformLocation(const std::string &name)
{
	return glGetUniformLocation(m_glId, name.c_str());
}

void
Shader::bindAttribute(GLuint attribute, const std::string &name)
{
	glBindAttribLocation(m_glId, attribute, name.c_str());
}

void
Shader::loadBool(GLuint &loc, bool &b)
{
	glUniform1i(loc, b ? 1 : 0);
}

void
Shader::loadFloat(GLuint &loc, float &f)
{
	glUniform1f(loc, f);
}

void
Shader::loadVec3(GLuint &loc, const glm::vec3 &v)
{
	glUniform3f(loc, v.x, v.y, v.z);
}

void
Shader::loadMat4(GLuint &loc, const glm::mat4 &m)
{
	glUniformMatrix4fv(loc, 1, false, &m[0][0]);
}

