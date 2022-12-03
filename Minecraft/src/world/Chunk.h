#pragma once

#include "Block.h"
#include <vector>

namespace Mc
{
	class Chunk
	{
	public:

		Chunk();

		Chunk(glm::vec3 position);

		Chunk(const Chunk&);

		const std::vector<Block>& GetBlocks() const;

		glm::vec3 GetPosition() const;

	public:

		static const uint32_t BlocksPerChunk();

	private:

		std::vector<Block> m_blocks;

		glm::vec3 m_position;

	public:

		static const uint32_t s_chunkHeight = 256;

		static const uint32_t s_chunkWidth = 16;

		static const uint32_t s_chunkLength = 16;
	};
}