#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_renderID);
	glBindVertexArray(m_renderID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_renderID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

size_t VertexArray::calcStride()
{
	size_t stride = 0;
	for (int i = 0; i < m_attribs.size(); i++)
		stride += getSizeofType(m_attribs[i].type) * m_attribs[i].count;
	return stride;
}

size_t VertexArray::getSizeofType(GLenum type)
{
	switch (type)
	{
	case GL_FLOAT:         return 4;
	case GL_BOOL:          return 1;
	case GL_UNSIGNED_INT:  return 4;
	case GL_UNSIGNED_BYTE: return 1;
	}
}

void VertexArray::push(GLint count, GLenum type, GLboolean normalized)
{
	m_attribs.push_back({ count, type, normalized });
	GLuint stride = calcStride();
	uint32_t offset = 0;
	for (int i = 0; i < m_attribs.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
			m_attribs[i].count,
			m_attribs[i].type,
			m_attribs[i].normalized,
			stride, (const void*)offset
		);
		offset += getSizeofType(m_attribs[i].type) * m_attribs[i].count;
	}
}