#pragma once

#include "../glm/glm.hpp"

struct Vertex
{
	Vertex() : position(), texCoords() {}

	Vertex(const glm::vec3& pos, const glm::vec2& coords)
		: position(pos), texCoords(coords) {}

	Vertex(const Vertex& v)
	{
		position = v.position;
		texCoords = v.texCoords;
	}

	Vertex(Vertex&& v) noexcept
		: position(std::move(v.position)), texCoords(std::move(v.texCoords)) {}

	Vertex& operator=(Vertex&& v) noexcept
	{
		if (this != &v)
		{
			position = v.position;
			texCoords = v.texCoords;
		}
		return *this;
	}

	Vertex& operator=(const Vertex& v)
	{
		if (this != &v)
		{
			position = v.position;
			texCoords = v.texCoords;
		}
		return *this;
	}

	glm::vec3 position;
	glm::vec2 texCoords;
};