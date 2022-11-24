#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Window.h"
#include "TextureAtlas.h"
#include "../Util/Ref.h"

class Renderer
{
public:

	static const Renderer& Get();

	static void SetTextureAtlasFilePath(const std::string& filepath, uint32_t countWidth, uint32_t countHeight);

	static void SetVertexData(Vertex* vertices, size_t size);

	static void SetIndexData(uint32_t* indices, size_t size);

	static void SetWindowViewDimensions(float width, float height);

	static void OnUpdate();

	static void OnInit();

	static Ref<Window> GetWindow();

	static Ref<Camera> GetCamera();

private:

	Renderer() = default;

	Renderer(const Renderer&) = delete;

	void SetVertexBufferData(Vertex* vertices, size_t size);

	void SetIndexBufferData(uint32_t* indices, size_t size);

	void SetRendererTextureAtlasFilePath(const std::string& filepath, uint32_t countWidth, uint32_t countHeight);

	void SetRendererWindowViewDimensions(float width, float height);

	void OnRendererUpdate();

	void OnRendererInit();

	Ref<Window> GetRenderingWindow();

	Ref<Camera> GetWindowCamera();

private:

	static Renderer s_instance;

private:

	Ref<VertexBuffer> m_vertexBuffer;
	Ref<IndexBuffer> m_indexBuffer;
	Ref<VertexArray> m_vertexArray;
	Ref<ShaderProgram> m_shaderProgram;
	Ref<Window> m_window;

	float m_windowHeight = 800.0f;
	float m_windowWidth = 800.0f;

	std::string m_textureAtlasFilePath;
	uint32_t m_countTextureAtlasTextureWidth;
	uint32_t m_countTextureAtlasTextureHeight;
};