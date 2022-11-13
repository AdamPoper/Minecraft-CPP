#pragma once

#include <array>

#include "../Util/Vertex.h"
#include "../Logger/Logger.h"
#include "../Renderer/TextureAtlas.h"

enum class Texture
{
	GRASS,
	DIRT,
	DIRT_GRASS,
	WOOD_OAK,
	WOOD_OAK_PLANK,
	STONE,
	COBBLE_STONE,
	SAND,
	GLASS,
	AIR
};

enum class Direction
{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
};

class BlockFace 
{

public:

	BlockFace() = default;

	BlockFace(Texture texture, Direction direction);

	const std::array<Vertex, 4>& GetVertices() const;	

private:

	void InitVertexPositions();

	void InitVertexTextureCoords();

private:

	static std::array<glm::vec3, 8> s_positions;

	static std::array<glm::vec2, 4> s_texCoords;

private:

	std::array<Vertex, 4> m_vertices;
	Texture m_texture;
	Direction m_direction;
};