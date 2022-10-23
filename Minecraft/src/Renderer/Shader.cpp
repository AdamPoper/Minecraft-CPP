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

void ShaderProgram::AttachShader(std::shared_ptr<Shader>& shader)
{
	m_shaders.push_back(shader);
}

void ShaderProgram::CreateShaderProgram()
{
	for (std::shared_ptr<Shader> shader : m_shaders)
		glAttachShader(m_renderID, shader->GetRenderID());
	glLinkProgram(m_renderID);
	glValidateProgram(m_renderID);
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
	for (std::shared_ptr<Shader> shader : m_shaders)
		glDeleteShader(shader->GetRenderID());
}

void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	int location = glGetUniformLocation(m_renderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}