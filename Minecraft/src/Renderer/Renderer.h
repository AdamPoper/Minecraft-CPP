#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Window.h"
#include "TextureAtlas.h"

class Renderer
{
public:

	static Renderer& Get();

	static void SetVertexData(Vertex* vertices, size_t size);

	static void SetIndexData(uint32_t* indices, size_t size);

	static void OnUpdate();

	static void OnInit();

	static std::shared_ptr<Window> GetWindow();

	static std::shared_ptr<Camera> GetCamera();

private:

	Renderer();

	Renderer(const Renderer&) = delete;

	void SetVertexBufferData(Vertex* vertices, size_t size);

	void SetIndexBufferData(uint32_t* indices, size_t size);

	void OnRendererUpdate();

	void OnRendererInit();

	std::shared_ptr<Window> GetRenderingWindow();

	std::shared_ptr<Camera> GetWindowCamera();

private:

	static Renderer s_instance;

private:

	std::shared_ptr<VertexBuffer> m_vertexBuffer;
	std::shared_ptr<IndexBuffer> m_indexBuffer;
	std::shared_ptr<VertexArray> m_vertexArray;
	std::shared_ptr<ShaderProgram> m_shaderProgram;
	std::shared_ptr<Window> m_window;

	float m_defaultWindowHeight = 800.0f;
	float m_defaultWindowWidth = 800.0f;

	glm::mat4 m_model;
};