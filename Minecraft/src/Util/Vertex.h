#pragma once

#include "../glm/glm.hpp"

struct Vertex
{
	Vertex() : position(), color() {}

	Vertex(const glm::vec3& pos, const glm::vec4& col)
		: position(pos), color(col) {}

	Vertex(const Vertex& v)
	{
		position = v.position;
		color = v.color;
	}

	Vertex(Vertex&& v) noexcept
		: position(std::move(v.position)), color(std::move(v.color)) {}

	Vertex& operator=(Vertex&& v) noexcept
	{
		if (this != &v)
		{
			position = v.position;
			color = v.color;
		}
		return *this;
	}

	glm::vec3 position;
	glm::vec4 color;
};