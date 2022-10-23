#pragma once
#include <GL/glew.h>
#include <vector>
#include "../glm/glm.hpp"
#include "../Util/Vertex.h"

struct VertexAttrib
{
	GLint count;
	GLenum type;
	GLboolean normalized;
};

class VertexArray
{
public:
	VertexArray();

	void Bind() const;

	void UnBind() const;

	void push(GLint count, GLenum type, GLboolean normalized);
private:

	size_t getSizeofType(GLenum type);

	size_t calcStride();

private:
	GLuint m_renderID;
	std::vector<VertexAttrib> m_attribs;
};