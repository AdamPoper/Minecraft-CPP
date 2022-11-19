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

	VertexBuffer(std::size_t capacity);

	VertexBuffer(Vertex* data, std::size_t size);

	void SetData(Vertex* data, std::size_t size);

	void Bind();

	void UnBind();

	std::size_t GetCount() const;

private:

	std::size_t m_size;

	std::size_t m_capacity;

	static const std::size_t s_defaultCapacity = 4800000;
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
	
	uint32_t m_count;

	static const std::size_t s_defaultSize = 1000000;
};