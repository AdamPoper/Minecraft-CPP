#pragma once

#include <string>
#include <memory>

#include "GL/glew.h"
#include "../glm/glm.hpp"
#include "stb_image/stb_image.h"
#include "../Logger/Logger.h"

class TextureAtlas
{
public:

	static void Create(const std::string& filepath, uint32_t countTexturesWidth, uint32_t countTexturesHeight);

	static const TextureAtlas& Get();

	static void Bind();

	static void UnBind();

	static glm::vec2 GetDimensions();

	static uint32_t GetTextureWidth();

	static uint32_t GetTextureHeight();

	static const std::string& GetOpenGLUniformID();

private:

	TextureAtlas();

	~TextureAtlas();

	TextureAtlas(const TextureAtlas&) = delete;

	void CreateTextureAtlas(const std::string& filepath, uint32_t countTexturesWidth, uint32_t countTexturesHeight);

	void BindTextureAtlas() const;

	void UnBindTextureAtlas() const;

	void LoadTextureFromFile();

	void GenTexture();

	glm::ivec2 Dimensions() const;

	uint32_t TextureWidth() const;

	uint32_t TextureHeight() const;

	const std::string& OpenGLUniformID() const;

private:

	static TextureAtlas s_textureAtlasInstance;

	std::string m_filePath;

	const std::string m_openGLUniformID;

	uint8_t* m_buffer;

	uint32_t m_renderID;

	int32_t m_bpp;

	glm::ivec2 m_dimensions;

	uint32_t m_countTexturesWidth;

	uint32_t m_countTexturesHeight;
};