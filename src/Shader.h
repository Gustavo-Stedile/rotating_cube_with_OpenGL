#pragma once 

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertexSource; 
	std::string fragmentSource;
};

class Shader 
{
private:
  std::string filepath;
  unsigned int rendererID;
  std::unordered_map<std::string, unsigned int> uniformLocationCache;

public:
  Shader(const std::string &filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
  void setUniformMat4f(const std::string &name, const glm::mat4& matrix);

private:
  ShaderProgramSource parseShader(const std::string &filepath);
  unsigned int compileShader(unsigned int type, const std::string &source);
  unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
  unsigned int getUniformLocation(const std::string& name);
};