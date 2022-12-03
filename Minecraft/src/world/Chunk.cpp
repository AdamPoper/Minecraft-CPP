#include "Chunk.h"

namespace Mc
{
	Chunk::Chunk() :
		m_position(0.0f, 0.0f, 0.0f)
	{
		m_blocks.reserve(BlocksPerChunk());
	}

	Chunk::Chunk(glm::vec3 position) :
		m_position(position)
	{
		m_blocks.reserve(BlocksPerChunk());

		for (int x = 0; x < s_chunkWidth; x++)
		{
			for (int z = 0; z < s_chunkLength; z++)
			{
				for (int y = 0; y < s_chunkHeight; y++)
				{
					m_blocks.emplace_back(BlockType::DIRT, position);
					position.y += 1.0f;
				}
				position.y = m_position.y;
				position.z += 1.0f;
			}
			position.z = m_position.z;
			position.x += 1.0f;
		}
	}

	Chunk::Chunk(const Chunk& chunk)
	{

	}

	const std::vector<Block>& Chunk::GetBlocks() const
	{
		return m_blocks;
	}

	const uint32_t Chunk::BlocksPerChunk()
	{
		return s_chunkHeight * s_chunkLength * s_chunkWidth;
	}

	glm::vec3 Chunk::GetPosition() const
	{
		return m_position;
	}
}