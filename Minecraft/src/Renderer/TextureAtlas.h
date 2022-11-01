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

	static TextureAtlas& Get();

	void Create();

	void Bind() const;

	void UnBind() const;

	glm::ivec2 Dimensions() const;

	const std::string& GetOpenGLUniformID() const;

private:

	TextureAtlas();

	~TextureAtlas();

	TextureAtlas(const TextureAtlas&) = delete;

	void LoadTextureFromFile();

	void GenTexture();

private:

	static TextureAtlas s_textureAtlas;

	const std::string m_filePath;

	const std::string m_openGLUniformID;

	uint8_t* m_buffer;

	uint32_t m_renderID;

	int32_t m_bpp;

	glm::ivec2 m_dimensions;

	static uint32_t s_referenceCounter;
};