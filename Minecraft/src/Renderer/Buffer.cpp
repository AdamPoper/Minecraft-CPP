#include "Buffer.h"

uint32_t Buffer::GetRenderID() const
{
	return m_renderID;
}

VertexBuffer::VertexBuffer(Vertex* data, std::size_t size)
	: m_size(size)
{	
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, (const void*)data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::size_t size)
{
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
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
	m_size = size;
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, (const void*)data);
}

/*
		Index Buffer
*/

IndexBuffer::IndexBuffer(uint32_t* data, uint32_t count)
	:m_count(count)
{	
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_count, (const void*)data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(std::size_t size)
	:m_count(size)
{
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size) * m_count, nullptr, GL_DYNAMIC_DRAW);
}

void IndexBuffer::SetData(uint32_t* data, uint32_t count)
{
	m_count = count;
	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * m_count, (const void*)data);
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