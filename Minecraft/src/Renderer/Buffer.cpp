#include "Buffer.h"

VertexBuffer::VertexBuffer() :
	m_capacity(s_defaultCapacity),
	m_size(0)
{
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(Vertex* data, uint32_t count) :
	m_size(sizeof(Vertex) * count), 
	m_capacity(sizeof(Vertex) * count)
{	
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, m_capacity, (const void*)data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(uint32_t count) :
	m_size(0),
	m_capacity(sizeof(Vertex) * count)
{
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

uint32_t Buffer::GetRenderID() const
{
	return m_renderID;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::size_t VertexBuffer::GetCount() const
{
	return m_size;
}

void VertexBuffer::SetData(Vertex* data, std::size_t size)
{
	Bind();
	std::size_t dataSize = size * sizeof(Vertex);
	if (dataSize >= m_capacity)
	{
		Resize(dataSize);
	}
	m_size = dataSize;
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, (const void*)data);
}

void VertexBuffer::Resize(std::size_t bytes)
{
	m_capacity += bytes;
	glBufferData(GL_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::Resize()
{
	m_capacity *= 2;
	glBufferData(GL_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

/*
		Index Buffer
*/

IndexBuffer::IndexBuffer() :
	m_capacity(s_defaultCapacity),
	m_size(0)
{
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::IndexBuffer(uint32_t* data, uint32_t count) :
	m_count(count),
	m_size(sizeof(uint32_t) * count),
	m_capacity(sizeof(uint32_t) * count)
{	
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_capacity, (const void*)data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(std::size_t size) :
	m_count(size),
	m_size(0),
	m_capacity(sizeof(uint32_t) * size)
{
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

void IndexBuffer::SetData(uint32_t* data, uint32_t count)
{
	Bind();
	std::size_t dataSize = sizeof(uint32_t) * count;
	if (dataSize >= m_capacity)
	{
		Resize(dataSize);
	}
	m_count = count;
	m_size = dataSize;
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, dataSize, (const void*)data);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::size_t IndexBuffer::GetCount() const
{
	return m_count;
}

void IndexBuffer::Resize(std::size_t bytes)
{
	m_capacity += bytes;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}

void IndexBuffer::Resize()
{
	m_capacity *= 2;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_capacity, nullptr, GL_DYNAMIC_DRAW);
}