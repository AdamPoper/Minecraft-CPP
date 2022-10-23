#pragma once

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "../Logger/Logger.h"
#include "../glm/glm.hpp"

class Shader
{
public:
	
	Shader();

	template<typename T>
	static T CreateShader()
	{
		typedef T ShaderType;
		if (std::is_base_of<Shader, ShaderType>::value)
		{
			ShaderType shader;
			shader.LoadShader();
			shader.CompileShader();
			return shader;
		}
		else
		{
			MC_CONSOLE_LOG("Invalid Shader Type");
			return T();
		}
	}

	Shader(const Shader&);

	uint32_t GetRenderID() const;

public:

	void CompileShader();

	void LoadShader();

protected:
	std::string m_filePath;
	std::string m_sourceCode;
	uint32_t m_renderID;
};

class ShaderProgram
{
public:

	ShaderProgram();

	void AttachShader(const Shader& shader);

	void Bind() const;

	void UnBind() const;

	void CreateShaderProgram();

	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:

	void DeleteShaders();

private:
	std::vector<Shader> m_shaders;
	uint32_t m_renderID;
};

class VertexShader : public Shader
{
public:
	VertexShader();
};

class FragmentShader : public Shader
{
public:
	FragmentShader();
};