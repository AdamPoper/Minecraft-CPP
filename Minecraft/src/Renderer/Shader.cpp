#include "Shader.h"

Shader::Shader() : m_renderID(0) {}

Shader::Shader(const Shader& shader)
{
	m_filePath = shader.m_filePath;
	m_sourceCode = shader.m_sourceCode;
	m_renderID = shader.m_renderID;
	MC_CONSOLE_LOG("Shader Copied");
}

Shader::Shader(Shader&& shader) noexcept
	: m_filePath(std::move(shader.m_filePath)),
	m_renderID(shader.m_renderID),
	m_sourceCode(shader.m_sourceCode)
{
	MC_CONSOLE_LOG("Shader Moved");
}

Shader& Shader::operator=(Shader&& shader) noexcept
{
	if (this != &shader)
	{
		m_renderID = std::move(shader.m_renderID);
		m_filePath = std::move(shader.m_filePath);
		m_sourceCode = std::move(shader.m_sourceCode);
		MC_CONSOLE_LOG("Shader Moved");
	}
	return *this;
}

VertexShader::VertexShader()
{
	m_filePath = "res/shaders/vertexShader.shader";
	m_renderID = glCreateShader(GL_VERTEX_SHADER);
	MC_CONSOLE_LOG("Vertex Shader Created");
}

FragmentShader::FragmentShader()
{
	m_filePath = "res/shaders/fragmentShader.shader";
	m_renderID = glCreateShader(GL_FRAGMENT_SHADER);
	MC_CONSOLE_LOG("Fragment Shader Created");
}

void Shader::LoadShader()
{
	std::string line;
	std::stringstream sstream;
	std::fstream filestream;
	filestream.open(m_filePath);
	if (filestream.fail())
	{
		MC_CONSOLE_LOG("Shader File Failed To Open");
		return;
	}
	while (std::getline(filestream, line))
		sstream << line << std::endl;
	m_sourceCode = sstream.str();
}

void Shader::CompileShader()
{
	const char* c_str = m_sourceCode.c_str();
	glShaderSource(m_renderID, 1, &c_str, nullptr);
	glCompileShader(m_renderID);
}

uint32_t Shader::GetRenderID() const
{
	return m_renderID;
}

ShaderProgram::ShaderProgram()
{
	m_shaders.reserve(2);
	m_renderID = glCreateProgram();
}

void ShaderProgram::AttachShader(Scope<Shader>& shader)
{
	m_shaders.push_back(std::move(shader));
}

void ShaderProgram::CreateShaderProgram()
{
	for (const Scope<Shader>& shader : m_shaders)
		glAttachShader(m_renderID, shader->GetRenderID());
	glValidateProgram(m_renderID);
	glLinkProgram(m_renderID);
	int linkSuccess;
	glGetProgramiv(m_renderID, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_renderID, 512, NULL, infoLog);
		printf("shader id: %d failed\n", m_renderID);
		printf("%s\n", infoLog);
	}
	Bind();
	DeleteShaders();
}

void ShaderProgram::Bind() const
{
	glUseProgram(m_renderID);
}

void ShaderProgram::UnBind() const
{
	glUseProgram(0);
}

void ShaderProgram::DeleteShaders()
{
	for (Scope<Shader>& shader : m_shaders)
		glDeleteShader(shader->GetRenderID());
}

uint32_t ShaderProgram::GetUniformLocation(const std::string& name)
{
	uint32_t location;
	auto iter = m_uniforms.find(name);
	if (iter != m_uniforms.end())
	{
		location = iter->second;
	}
	else
	{
		location = glGetUniformLocation(m_renderID, name.c_str());
		if (location == GL_INVALID_INDEX)
		{
			MC_CONSOLE_LOG("Invalid Index");
		}
		else
		{
			m_uniforms.insert(std::pair<std::string, uint32_t>(name, location));
		}
	}
	return location;
}

void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	uint32_t location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetUniform1i(const std::string& name, uint32_t value)
{
	uint32_t location = GetUniformLocation(name);
	glUniform1i(location, value);
}