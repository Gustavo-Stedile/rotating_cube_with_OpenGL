#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 


#include <GL/glew.h>

Shader::Shader(const std::string &filepath)
  : filepath(filepath), rendererID(0)
{
	ShaderProgramSource source = parseShader(filepath);
	rendererID	= createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(rendererID);
}

void Shader::bind() const
{
	glUseProgram(rendererID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	glUniform4f(getUniformLocation(name), f0, f1, f2, f3);
}

unsigned int Shader::getUniformLocation(const std::string &name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end()) 
		return uniformLocationCache[name];

	unsigned int location = glGetUniformLocation(rendererID, name.c_str());
	if (location == -1) std::cout << "warning: uniform " << name << " doesnt exist";
	uniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::parseShader(const std::string &filepath)
{
	std::ifstream stream(filepath);
	if (!stream.is_open()) std::cout << "deu ruim";

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;

			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}




unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		std::cout << "deu ruim\n";
	}
	return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
