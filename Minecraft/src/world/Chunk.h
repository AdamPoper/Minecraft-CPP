#pragma once

#include "Block.h"
#include "../Util/Ref.h"
#include "../Util/PerlinNoise.h"

#include <vector>
#include <unordered_map>

struct Vec3KeyHasher
{
	std::size_t operator()(const glm::vec3& vec) const
	{
		using std::size_t;
		using std::hash;

		return ((hash<float>()(vec.x)
			^ (hash<float>()(vec.y) << 1)) >> 1)
			^ (hash<float>()(vec.z) << 1);
	}
};

namespace Mc
{
	class Chunk
	{
	public:

		Chunk();

		Chunk(glm::vec3 position);

		Chunk(const Chunk&);

		const std::vector<Block>& GetBlocks() const;

		std::vector<Block>& GetBlocks();

		glm::vec3 GetPosition() const;

		void SetDisableChunkFace(Direction dir);

		const Block* QueryForBlockByPosition(glm::vec3 position) const;

		Block* QueryForBlockByPosition(glm::vec3 position);

		const std::vector<std::vector<Block>::iterator>& GetChunkFaceByDirection(Direction dir) const;

		std::vector<std::vector<Block>::iterator>& GetChunkFaceByDirection(Direction dir);

	public:

		static const uint32_t BlocksPerChunk();

		static Ref<Chunk> CreateChunk(glm::vec3 position);

		static void SetPerlinNoise(Ref<PerlinNoise> noise);

	private:

		void Create(glm::vec3 position);

		void CreateChunkPartly(uint32_t heightValue, BlockType type, glm::vec3& position);

		void OptimizeChunkBruteForce();

		void OptimizeChunkHashing();

		void CheckNeighboringBlocksBruteForce(Block& block);

		void CheckNeighboringBlocksHashing(Block& block);

		void CheckBlock(Block& testBlock, glm::vec3 position, bool& exists, Direction direction);

		void PopulateChunkFacesX(Direction direction, glm::vec3 startingPosition);

		void PopulateChunkFacesZ(Direction direction, glm::vec3 startingPosition);

		void PopulateChunkFacesBottom();

	private:

		std::vector<Block> m_blocks;

		std::unordered_map<glm::vec3, std::vector<Block>::iterator, Vec3KeyHasher> m_blockPositions;

		std::unordered_map<Direction, std::vector<std::vector<Block>::iterator>> m_chunkFaces;
		
		glm::vec3 m_position;

		static Ref<PerlinNoise> s_perlinNoise;

	public:

		static const uint32_t s_chunkHeight = 128;

		static const uint32_t s_chunkWidth = 16;

		static const uint32_t s_chunkLength = 16;
	};
}