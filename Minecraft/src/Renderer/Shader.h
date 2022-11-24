#pragma once

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "../Util/Ref.h"
#include "../Logger/Logger.h"
#include "../glm/glm.hpp"

class Shader
{
public:
	
	Shader();

	template<typename T>
	static Scope<T> CreateShader()
	{
		typedef T ShaderType;
		if (std::is_base_of<Shader, ShaderType>::value)
		{
			Scope<ShaderType> shader = CreateScope<ShaderType>();
			shader->LoadShader();
			shader->CompileShader();
			return shader;
		}
		else
		{
			MC_CONSOLE_LOG("Invalid Shader Type");
			return CreateScope<T>();
		}
	}

	Shader(const Shader& shader);

	Shader(Shader&& shader) noexcept;

	Shader& operator=(Shader&& shader) noexcept;

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

	void AttachShader(Scope<Shader>& shader);

	void Bind() const;

	void UnBind() const;

	void CreateShaderProgram();

	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	void SetUniform1i(const std::string& name, uint32_t value);

private:

	void DeleteShaders();

private:
	std::vector<Scope<Shader>> m_shaders;
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