#include "Chunk.h"

namespace Mc
{
	Chunk::Chunk() :
		m_position(0.0f, 0.0f, 0.0f),
		m_blockPositions()
	{
		m_blocks.reserve(BlocksPerChunk());
	}

	Chunk::Chunk(glm::vec3 position) :
		m_position(position),
		m_blockPositions()
	{
		m_blocks.reserve(BlocksPerChunk());
		Create(position);
	}

	Chunk::Chunk(const Chunk& chunk)
	{

	}

	void Chunk::Create(glm::vec3 position)
	{
		for (int x = 0; x < s_chunkWidth; x++)
		{
			for (int z = 0; z < s_chunkLength; z++)
			{
				for (int y = 0; y < s_chunkHeight; y++)
				{
					m_blocks.emplace_back(BlockType::DIRT, position);
					m_blockPositions.insert(
						std::pair<glm::vec3, std::vector<Block>::iterator>(
							position, --m_blocks.end()));
					position.y += 1.0f;
				}
				position.y = m_position.y;
				position.z += 1.0f;
			}
			position.z = m_position.z;
			position.x += 1.0f;
		}
#define HASHING 1
#if HASHING
		OptimizeChunkHashing();
#else
		OptimizeChunkBruteForce();
#endif
	}

	glm::vec3 Chunk::GetPosition() const
	{
		return m_position;
	}

	const std::vector<Block>& Chunk::GetBlocks() const
	{
		return m_blocks;
	}

	std::vector<Block>& Chunk::GetBlocks()
	{
		return m_blocks;
	}

	Ref<Chunk> Chunk::CreateChunk(glm::vec3 position)
	{
		return CreateRef<Chunk>(position);
	}

	const uint32_t Chunk::BlocksPerChunk()
	{
		return s_chunkHeight * s_chunkLength * s_chunkWidth;
	}

	void Chunk::CheckBlock(Block& testBlock, glm::vec3 position, bool& exists, Direction direction)
	{
		auto mapIter = m_blockPositions.find(position);
		if (mapIter != m_blockPositions.end())
		{
			exists = true;
			auto blockIter = mapIter->second;
			if (blockIter->GetBlockType() == BlockType::AIR)
			{
				testBlock.SetBlockFaceToRender(direction);
			}
		}
	}

	void Chunk::CheckNeighboringBlocksHashing(Block& testBlock)
	{
		glm::vec3 blockPosition = testBlock.GetPosition();

		glm::vec3 front = blockPosition  + glm::vec3( 0.0f,  0.0f, -1.0f);
		glm::vec3 back = blockPosition   + glm::vec3( 0.0f,  0.0f,  1.0f);
		glm::vec3 right = blockPosition  + glm::vec3(-1.0f,  0.0f,  0.0f);
		glm::vec3 left = blockPosition   + glm::vec3( 1.0f,  0.0f,  0.0f);
		glm::vec3 top = blockPosition    + glm::vec3( 0.0f, -1.0f,  0.0f);
		glm::vec3 bottom = blockPosition + glm::vec3( 0.0f,  1.0f,  0.0f);

		bool frontExists = false;
		bool backExists = false;
		bool rightExists = false;
		bool leftExists = false;
		bool topExists = false;
		bool bottomExists = false;

		CheckBlock(testBlock, front,  frontExists,  Direction::FRONT);
		CheckBlock(testBlock, back,   backExists,   Direction::BACK);
		CheckBlock(testBlock, right,  rightExists,  Direction::RIGHT);
		CheckBlock(testBlock, left,   leftExists,   Direction::LEFT);
		CheckBlock(testBlock, top,    topExists,    Direction::TOP);
		CheckBlock(testBlock, bottom, bottomExists, Direction::BOTTOM);

		if (!frontExists)
			testBlock.SetBlockFaceToRender(Direction::FRONT);
		if (!backExists)
			testBlock.SetBlockFaceToRender(Direction::BACK);
		if (!rightExists)
			testBlock.SetBlockFaceToRender(Direction::RIGHT);
		if (!leftExists)
			testBlock.SetBlockFaceToRender(Direction::LEFT);
		if (!topExists)
			testBlock.SetBlockFaceToRender(Direction::TOP);
		if (!bottomExists)
			testBlock.SetBlockFaceToRender(Direction::BOTTOM);
	}

	void Chunk::CheckNeighboringBlocksBruteForce(Block& testBlock)
	{
		glm::vec3 blockPosition = testBlock.GetPosition();

		glm::vec3 front = blockPosition + glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 back = blockPosition + glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 right = blockPosition + glm::vec3(-1.0f, 0.0f, 0.0f);
		glm::vec3 left = blockPosition + glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 top = blockPosition + glm::vec3(0.0f, -1.0f, 0.0f);
		glm::vec3 bottom = blockPosition + glm::vec3(0.0f, 1.0f, 0.0f);

		bool frontExists = false;
		bool backExists = false;
		bool rightExists = false;
		bool leftExists = false;
		bool topExists = false;
		bool bottomExists = false;

		for (Block& block : m_blocks)
		{
			if (block.GetPosition() == testBlock.GetPosition())
			{
				continue;
			}
		
			if (block.GetPosition() == front)
			{
				frontExists = true;
				if (block.GetBlockType() == BlockType::AIR)
				{
					testBlock.SetBlockFaceToRender(Direction::FRONT);
				}
			}
			else if (block.GetPosition() == back)
			{
				backExists = true;
				if (block.GetBlockType() == BlockType::AIR)
				{
					testBlock.SetBlockFaceToRender(Direction::BACK);
				}
			}
			else if (block.GetPosition() == right)
			{
				rightExists = true;
				if (block.GetBlockType() == BlockType::AIR)
				{
					testBlock.SetBlockFaceToRender(Direction::RIGHT);
				}
			}
			else if (block.GetPosition() == left)
			{
				leftExists = true;
				if (block.GetBlockType() == BlockType::AIR)
				{
					testBlock.SetBlockFaceToRender(Direction::LEFT);
				}
			}
			else if (block.GetPosition() == top)
			{
				topExists = true;
				if (block.GetBlockType() == BlockType::AIR)
				{
					testBlock.SetBlockFaceToRender(Direction::TOP);
				}
			}
			else if (block.GetPosition() == bottom)
			{
				bottomExists = true;
				if (block.GetBlockType() == BlockType::AIR)
				{
					testBlock.SetBlockFaceToRender(Direction::BOTTOM);
				}
			}
		}
		if (!frontExists)
			testBlock.SetBlockFaceToRender(Direction::FRONT);
		if (!backExists)
			testBlock.SetBlockFaceToRender(Direction::BACK);
		if (!rightExists)
			testBlock.SetBlockFaceToRender(Direction::RIGHT);
		if (!leftExists)
			testBlock.SetBlockFaceToRender(Direction::LEFT);
		if (!topExists)
			testBlock.SetBlockFaceToRender(Direction::TOP);
		if (!bottomExists)
			testBlock.SetBlockFaceToRender(Direction::BOTTOM);
	}

	void Chunk::OptimizeChunkHashing()
	{
		for (Block& block : m_blocks)
		{
			CheckNeighboringBlocksHashing(block);
		}
	}

	void Chunk::OptimizeChunkBruteForce()
	{
		for (Block& block : m_blocks)
		{
			CheckNeighboringBlocksBruteForce(block);
		}
	}
}