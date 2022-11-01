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

	VertexBuffer() = default;

	VertexBuffer(std::size_t size);

	VertexBuffer(Vertex* data, std::size_t size);

	void SetData(Vertex* data, std::size_t size);

	void Bind();

	void UnBind();

	std::size_t GetCount() const;

private:

	std::size_t m_size;
};

class IndexBuffer : public Buffer
{
public:

	IndexBuffer() = default;

	IndexBuffer(uint32_t* data, uint32_t count);

	IndexBuffer(std::size_t size);

	void SetData(uint32_t* data, uint32_t count);

	void Bind();

	void UnBind();

	std::size_t GetCount() const;

private:
	
	uint32_t m_count;
};