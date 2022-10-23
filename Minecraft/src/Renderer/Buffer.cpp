#include "Buffer.h"

uint32_t Buffer::GetRenderID() const
{
	return m_renderID;
}

VertexBuffer::VertexBuffer(Vertex* data, std::size_t size)
	: m_buffer(size)
{
	for (int i = 0; i < size; i++)
		m_buffer[i] = std::move(data[i]);
	
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_buffer.size(), (const void*)m_buffer.data(), GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const Vertex* VertexBuffer::GetRawData() const
{
	return m_buffer.data();
}

constexpr std::size_t VertexBuffer::GetSize() const
{
	return m_buffer.size();
}

IndexBuffer::IndexBuffer(uint32_t* data, std::size_t size)
	:m_buffer(size)
{
	for (int i = 0; i < size; i++)
		m_buffer[i] = std::move(data[i]);
	
	glGenBuffers(1, &m_renderID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_buffer.size(), (const void*)m_buffer.data(), GL_STATIC_DRAW);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const uint32_t* IndexBuffer::GetRawData() const
{
	return m_buffer.data();
}

constexpr std::size_t IndexBuffer::GetSize() const
{
	return m_buffer.size();
}