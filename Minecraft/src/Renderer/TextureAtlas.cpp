#include "TextureAtlas.h"

TextureAtlas TextureAtlas::s_textureAtlas;
uint32_t TextureAtlas::s_referenceCounter = 0;

TextureAtlas::TextureAtlas()
	: m_filePath("res/textures/atlas.png"), m_openGLUniformID("u_Texture"),
	m_buffer(nullptr), m_dimensions(glm::vec2()), m_bpp(0), m_renderID(0)
{
	s_referenceCounter++;
	if (s_referenceCounter > 1)
	{
		MC_CONSOLE_LOG("No more than 1 texture atlas allowed");
	}
}

TextureAtlas& TextureAtlas::Get()
{
	return s_textureAtlas;
}

TextureAtlas::~TextureAtlas()
{
	MC_CONSOLE_LOG("Texture Atlas Destroyed");
	if (m_buffer != nullptr)
	{
		stbi_image_free(m_buffer);
	}
}

void TextureAtlas::Create()
{
	LoadTextureFromFile();
	if (m_buffer)
	{
		MC_CONSOLE_LOG("Texture Atlas Buffer Loaded");
		GenTexture();
	}
	else
	{
		MC_CONSOLE_LOG("Texture Atlas Buffer Not Loaded");
	}
}

void TextureAtlas::LoadTextureFromFile()
{
	stbi_set_flip_vertically_on_load(1);
	m_buffer = stbi_load(
		m_filePath.c_str(),
		&m_dimensions.x,
		&m_dimensions.y,
		&m_bpp,
		4
	);
}

void TextureAtlas::GenTexture()
{
	glGenTextures(1, &m_renderID);
	glBindTexture(GL_TEXTURE_2D, m_renderID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		m_dimensions.x, m_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		m_buffer
	);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(m_buffer);
	m_buffer = nullptr;
}

glm::ivec2 TextureAtlas::Dimensions() const
{
	return m_dimensions;
}

void TextureAtlas::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_renderID);
}

void TextureAtlas::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

const std::string& TextureAtlas::GetOpenGLUniformID() const
{
	return m_openGLUniformID;
}

uint32_t TextureAtlas::TextureSize() const
{
	return m_dimensions.x / 3.0f;
}