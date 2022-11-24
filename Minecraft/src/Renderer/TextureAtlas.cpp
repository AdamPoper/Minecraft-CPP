#include "TextureAtlas.h"

TextureAtlas TextureAtlas::s_textureAtlasInstance;

TextureAtlas::TextureAtlas() :
	m_openGLUniformID("u_Texture"),
	m_countTexturesWidth(0),
	m_countTexturesHeight(0)
{

}

const TextureAtlas& TextureAtlas::Get()
{
	return s_textureAtlasInstance;
}

TextureAtlas::~TextureAtlas()
{
	MC_CONSOLE_LOG("Texture Atlas Destroyed");
	if (m_buffer != nullptr)
	{
		stbi_image_free(m_buffer);
	}
}

void TextureAtlas::CreateTextureAtlas(const std::string& filepath, uint32_t countTexturesWidth, uint32_t countTexturesHeight)
{
	m_countTexturesWidth = countTexturesWidth;
	m_countTexturesHeight = countTexturesHeight;
	m_filePath = filepath;

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

void TextureAtlas::BindTextureAtlas() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_renderID);
}

void TextureAtlas::UnBindTextureAtlas() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

const std::string& TextureAtlas::OpenGLUniformID() const
{
	return m_openGLUniformID;
}

uint32_t TextureAtlas::TextureWidth() const
{
	return m_dimensions.x / m_countTexturesWidth;
}

uint32_t TextureAtlas::TextureHeight() const
{
	return m_dimensions.y / m_countTexturesHeight;
}

/*
	Instance Methods
*/

void TextureAtlas::Create(const std::string& filepath, uint32_t countTexturesWidth, uint32_t countTextureHeight)
{
	s_textureAtlasInstance.CreateTextureAtlas(filepath, countTexturesWidth, countTextureHeight);
}

void TextureAtlas::Bind()
{
	s_textureAtlasInstance.BindTextureAtlas();
}

void TextureAtlas::UnBind()
{
	s_textureAtlasInstance.UnBindTextureAtlas();
}

glm::vec2 TextureAtlas::GetDimensions()
{
	return s_textureAtlasInstance.Dimensions();
}

uint32_t TextureAtlas::GetTextureWidth()
{
	return s_textureAtlasInstance.TextureWidth();
}

uint32_t TextureAtlas::GetTextureHeight()
{
	return s_textureAtlasInstance.TextureHeight();
}
const std::string& TextureAtlas::GetOpenGLUniformID()
{
	return s_textureAtlasInstance.OpenGLUniformID();
}