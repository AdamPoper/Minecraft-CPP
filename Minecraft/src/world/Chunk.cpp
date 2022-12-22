#include "Chunk.h"

namespace Mc
{
	Ref<PerlinNoise> Chunk::s_perlinNoise = nullptr;

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
		glm::ivec2 noiseMid = s_perlinNoise->GetSize() / 2;
		uint32_t chunkCoreHeight = s_chunkHeight - (s_chunkHeight / 4);
		uint32_t chunkTerrainHeight = s_chunkHeight - chunkCoreHeight;
		for (int x = 0; x < s_chunkWidth; x++)
		{
			for (int z = 0; z < s_chunkLength; z++)
			{
				CreateChunkPartly(chunkCoreHeight, BlockType::DIRT, position);
				float rawNoiseValue = s_perlinNoise->
					GetNoise(glm::ivec2(position.x + noiseMid.x, position.z + noiseMid.y));
				uint32_t heightValue = static_cast<uint32_t>(rawNoiseValue * static_cast<const float>(chunkTerrainHeight));
				CreateChunkPartly(heightValue - 1, BlockType::DIRT, position);
				CreateChunkPartly(1, BlockType::DIRT_GRASS, position);
				CreateChunkPartly(chunkTerrainHeight - heightValue, BlockType::AIR, position);
				position.y = m_position.y;
				position.z += 1.0f;
			}
			position.z = m_position.z;
			position.x += 1.0f;
		}

		PopulateChunkFacesX(Direction::FRONT, m_position + glm::vec3(0.0f, 0.0f, static_cast<float>(s_chunkLength - 1)));
		PopulateChunkFacesZ(Direction::RIGHT, m_position + glm::vec3(static_cast<float>(s_chunkWidth - 1), 0.0f, 0.0f));
		PopulateChunkFacesX(Direction::BACK,  m_position);
		PopulateChunkFacesZ(Direction::LEFT,  m_position);
		PopulateChunkFacesBottom();

#define HASHING 1
#if HASHING
		OptimizeChunkHashing();
#else
		OptimizeChunkBruteForce();
#endif
	}

	void Chunk::CreateChunkPartly(uint32_t heightValue, BlockType type, glm::vec3& position)
	{
		for (int y = 0; y < heightValue; y++)
		{
			m_blocks.emplace_back(type, position);
			m_blockPositions.insert(
				std::pair<glm::vec3, std::vector<Block>::iterator>(
					position, --m_blocks.end()));
			position.y += 1.0f;
		}
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

	void Chunk::SetPerlinNoise(Ref<PerlinNoise> noise)
	{
		s_perlinNoise = noise;
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

		glm::vec3 front  = blockPosition + glm::vec3( 0.0f,  0.0f,  1.0f);
		glm::vec3 back   = blockPosition + glm::vec3( 0.0f,  0.0f, -1.0f);
		glm::vec3 right  = blockPosition + glm::vec3( 1.0f,  0.0f,  0.0f);
		glm::vec3 left   = blockPosition + glm::vec3(-1.0f,  0.0f,  0.0f);
		glm::vec3 top    = blockPosition + glm::vec3( 0.0f,  1.0f,  0.0f);
		glm::vec3 bottom = blockPosition + glm::vec3( 0.0f, -1.0f,  0.0f);

		bool frontExists  = false;
		bool backExists   = false;
		bool rightExists  = false;
		bool leftExists   = false;
		bool topExists    = false;
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

		glm::vec3 front  = blockPosition + glm::vec3( 0.0f,  0.0f,  1.0f);
		glm::vec3 back   = blockPosition + glm::vec3( 0.0f,  0.0f, -1.0f);
		glm::vec3 right  = blockPosition + glm::vec3( 1.0f,  0.0f,  0.0f);
		glm::vec3 left   = blockPosition + glm::vec3(-1.0f,  0.0f,  0.0f);
		glm::vec3 top    = blockPosition + glm::vec3( 0.0f,  1.0f,  0.0f);
		glm::vec3 bottom = blockPosition + glm::vec3( 0.0f, -1.0f,  0.0f);

		bool frontExists  = false;
		bool backExists   = false;
		bool rightExists  = false;
		bool leftExists   = false;
		bool topExists    = false;
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
			//block.SetBlockFaceToRender(Direction::FRONT);
			//block.SetBlockFaceToRender(Direction::BACK);
			//block.SetBlockFaceToRender(Direction::RIGHT);
			//block.SetBlockFaceToRender(Direction::LEFT);
			//block.SetBlockFaceToRender(Direction::TOP);
			//block.SetBlockFaceToRender(Direction::BOTTOM);
		}
	}

	void Chunk::OptimizeChunkBruteForce()
	{
		for (Block& block : m_blocks)
		{
			CheckNeighboringBlocksBruteForce(block);
		}
	}

	void Chunk::PopulateChunkFacesZ(Direction direction, glm::vec3 startingPosition)
	{
		glm::vec3 blockPosition = startingPosition;
		std::vector<std::vector<Block>::iterator> blockIters;
		blockIters.reserve(sizeof(std::vector<Block>::iterator) * s_chunkHeight * s_chunkLength);
		for (int y = 0; y < s_chunkHeight; y++)
		{
			for (int z = 0; z < s_chunkLength; z++)
			{
				auto iter = m_blockPositions.find(blockPosition);
				if (iter != m_blockPositions.end())
				{
					blockIters.emplace_back(iter->second);
				}
				blockPosition.z += 1.0f;
			}
			blockPosition.z = startingPosition.z;
			blockPosition.y += 1.0f;
		}
		m_chunkFaces.insert(std::pair<Direction, 
			std::vector<std::vector<Block>::iterator>>(direction, std::move(blockIters)));
	}

	void Chunk::PopulateChunkFacesX(Direction direction, glm::vec3 startingPosition)
	{
		glm::vec3 blockPosition = startingPosition;
		std::vector<std::vector<Block>::iterator> blockIters;
		blockIters.reserve(sizeof(std::vector<Block>::iterator) * s_chunkHeight * s_chunkLength);
		for (int y = 0; y < s_chunkHeight; y++)
		{
			for (int z = 0; z < s_chunkLength; z++)
			{
				auto iter = m_blockPositions.find(blockPosition);
				if (iter != m_blockPositions.end())
				{
					blockIters.emplace_back(iter->second);
				}
				blockPosition.x += 1.0f;
			}
			blockPosition.x = startingPosition.x;
			blockPosition.y += 1.0f;
		}
		m_chunkFaces.insert(std::pair<Direction,
			std::vector<std::vector<Block>::iterator>>(direction, std::move(blockIters)));
	}

	void Chunk::PopulateChunkFacesBottom()
	{
		glm::vec3 blockPosition = m_position;
		std::vector<std::vector<Block>::iterator> blockIters;
		blockIters.reserve(sizeof(std::vector<Block>::iterator) * s_chunkWidth * s_chunkLength);
		for (int x = 0; x < s_chunkWidth; x++)
		{
			for (int z = 0; z < s_chunkLength; z++)
			{
				auto iter = m_blockPositions.find(blockPosition);
				if (iter != m_blockPositions.end())
				{
					blockIters.emplace_back(iter->second);
				}
				blockPosition.z += 1.0f;
			}
			blockPosition.z = m_position.z;
			blockPosition.x += 1.0f;
		}
		m_chunkFaces.insert(std::pair<Direction,
			std::vector<std::vector<Block>::iterator>>(Direction::BOTTOM, std::move(blockIters)));
	}

	void Chunk::SetDisableChunkFace(Direction dir)
	{
		auto iter = m_chunkFaces.find(dir);
		if (iter != m_chunkFaces.end())
		{
			auto& blocks = iter->second;
			for (auto& blockIter : blocks)
			{
				blockIter->SetBlockFaceToNotRender(dir);
			}
		}
	}

	const Block* Chunk::QueryForBlockByPosition(glm::vec3 position) const
	{
		return QueryForBlockByPosition(position);
	}

	Block* Chunk::QueryForBlockByPosition(glm::vec3 position)
	{
		auto iter = m_blockPositions.find(position);
		if (iter != m_blockPositions.end())
		{
			return iter->second._Ptr;
		}
		return nullptr;
	}

	const std::vector<std::vector<Block>::iterator>& 
		Chunk::GetChunkFaceByDirection(Direction dir) const
	{
		return GetChunkFaceByDirection(dir);
	}

	std::vector<std::vector<Block>::iterator>&
		Chunk::GetChunkFaceByDirection(Direction dir)
	{
		auto iter = m_chunkFaces.find(dir);
		assert(iter == m_chunkFaces.end());
		return iter->second;
	}
}