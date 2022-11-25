#pragma once
#include <GL/glew.h>
#include "../Logger/Logger.h"
#include <vector>
#include "../Util/Vertex.h"

class Buffer
{
public:
	
	Buffer() = default;

	uint32_t GetRenderID() const;

	virtual void Bind() = 0;

	virtual void UnBind() = 0;

protected:

	uint32_t m_renderID;
};

class VertexBuffer : public Buffer
{
public:

	VertexBuffer();

	VertexBuffer(uint32_t count);

	VertexBuffer(Vertex* data, uint32_t count);

	void SetData(Vertex* data, std::size_t size);

	void Bind();

	void UnBind();

	std::size_t GetCount() const;

private:

	void Resize(std::size_t bytes);

	void Resize();

private:

	std::size_t m_size;

	std::size_t m_capacity;

	static const std::size_t s_defaultCapacity = sizeof(Vertex) * 10000;
};

class IndexBuffer : public Buffer
{
public:

	IndexBuffer();

	IndexBuffer(uint32_t* data, uint32_t count);

	IndexBuffer(std::size_t size);

	void SetData(uint32_t* data, uint32_t count);

	void Bind();

	void UnBind();

	std::size_t GetCount() const;

private:

	void Resize();

	void Resize(std::size_t count);

private:
	
	uint32_t m_count;

	std::size_t m_size;

	std::size_t m_capacity;

	static const std::size_t s_defaultCapacity = sizeof(uint32_t) * 100;
};