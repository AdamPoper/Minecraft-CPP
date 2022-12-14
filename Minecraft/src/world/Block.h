#pragma once

#include "BlockFace.h"
#include <map>
#include <vector>

namespace Mc
{
	enum class BlockType
	{
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

	class Block
	{
	public:

		static const uint32_t s_vertexCount = 24;

		static const uint32_t s_blockFacesCount = 6;

	public:

		Block();

		Block(BlockType blockType);

		Block(BlockType blockType, glm::vec3 position);

		Block(const Block& block);

		Block(Block&& block) noexcept;
			
		bool operator<(const Block&);

		const std::array<const Vertex*, s_vertexCount>& GetVertices() const;

		const std::array<BlockFace, s_blockFacesCount>& GetBlockFaces() const;

		void SetBlockType(BlockType blockType);

		BlockType GetBlockType() const;

		void Translate(glm::vec3 transform);

		void SetPosition(glm::vec3 position);

		glm::vec3 GetPosition() const;

		void SetBlockFaceToRender(Direction dir);

		void SetBlockFaceToNotRender(Direction dir);

		const std::vector<const Vertex*>& CreateMesh();

		const BlockFace& GetBlockFace(Direction direction) const;

	private:

		void InitBlockFaceTextures();

		void InitBlockFaceDirections();

		void SetBlockFaceVertices();

		BlockFace* GetBlockFaceByDirection(Direction direction);

		const BlockFace* GetBlockFaceByDirection(Direction direction) const;


	private:

		std::array<BlockFace, s_blockFacesCount> m_blockFaces;

		std::map<Direction, BlockFace*> m_blockFaceDirections;

		std::array<const Vertex*, s_vertexCount> m_blockFaceVertices;

		std::vector<const Vertex*> m_vertexMesh;

		glm::vec3 m_position;

		BlockType m_blockType;
	};
}