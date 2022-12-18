#include "World.h"

namespace Mc
{
	World World::s_instance;

	std::mutex World::s_chunksMutex;

	World::World()
	{
		m_chunks.reserve(m_defaultChunkRenderCount * m_defaultChunkRenderCount);

		uint32_t chunksX = m_defaultChunkRenderCount * 2;
		uint32_t chunksY = m_defaultChunkRenderCount * 2;
		m_terrainNoise = CreateRef<PerlinNoise>(
			glm::ivec2(chunksX * Chunk::s_chunkWidth, chunksY * Chunk::s_chunkLength));
		Chunk::SetPerlinNoise(m_terrainNoise);
	}

	void World::OnWorldInit()
	{
		glm::vec3 startingPosition(0.0f, m_worldBottom, 0.0f);		
		
		std::function<void(std::vector<Ref<Chunk>>*, glm::vec3)>
			generateChunkAsync = [](std::vector<Ref<Chunk>>* chunks, glm::vec3 position) {
			
			Ref<Chunk> chunk = Chunk::CreateChunk(position);
			std::lock_guard<std::mutex> lock(s_chunksMutex);
			chunks->push_back(chunk);
		};
		 
#define ASYNC 1
#if ASYNC

		MC_PROFILE_START("Creating World");
		
		GenerateChunksAsync(generateChunkAsync, 
							glm::vec3(0.0f, m_worldBottom, 0.0f), 
							glm::vec3(1.0f, 0.0f, 1.0f));

		GenerateChunksAsync(generateChunkAsync, 
							glm::vec3(0.0f, m_worldBottom, -1.0f * Chunk::s_chunkLength),
							glm::vec3(1.0f, 0.0f, -1.0f));
		
		GenerateChunksAsync(generateChunkAsync, 
							glm::vec3(-1.0f * Chunk::s_chunkWidth, m_worldBottom, 0.0f),
							glm::vec3(-1.0f, 0.0f,  1.0f));
		
		GenerateChunksAsync(generateChunkAsync, 
							glm::vec3(-1.0f * Chunk::s_chunkWidth, m_worldBottom, -1.0f * Chunk::s_chunkLength),
							glm::vec3(-1.0f, 0.0f, -1.0f));
		
		for (const std::future<void>& future : m_chunkFutures) future.wait();
		
		MC_PROFILE_END(Profiler::TimeFrame::SECONDS);
#else

		GenerateChunksSync(
			glm::vec3(0.0f, m_worldBottom, 0.0f),
			glm::vec3(1.0f, 0.0f, 1.0f));

		GenerateChunksSync(
			glm::vec3(0.0f, m_worldBottom, -1.0f * Chunk::s_chunkLength),
			glm::vec3(1.0f, 0.0f, -1.0f));
		
		GenerateChunksSync(
			glm::vec3(-1.0f * Chunk::s_chunkWidth, m_worldBottom, 0.0f),
			glm::vec3(-1.0f, 0.0f, 1.0f));
		
		GenerateChunksSync(
			glm::vec3(-1.0f * Chunk::s_chunkWidth, m_worldBottom, -1.0f * Chunk::s_chunkLength),
			glm::vec3(-1.0f, 0.0f, -1.0f));

#endif
	}

	const std::vector<Ref<Chunk>>& World::GetWorldChunks() const
	{
		return m_chunks;
	}

	const World& World::Get()
	{
		return s_instance;
	}

	uint32_t World::GetCountChunks() const
	{
		return m_chunks.size();
	}

	void World::GenerateChunksAsync(
		std::function<void(std::vector<Ref<Chunk>>*, glm::vec3)> generateChunkCallback,
		glm::vec3 startingPosition, 
		glm::vec3 relativeToPosition
	)
	{
		glm::vec3 position = startingPosition;
		for (int x = 0; x < m_defaultChunkRenderCount; x++)
		{
			for (int z = 0; z < m_defaultChunkRenderCount; z++)
			{
				m_chunkFutures.push_back(std::async(std::launch::async, generateChunkCallback, &m_chunks, position));
				position.z += static_cast<float>(Chunk::s_chunkLength * relativeToPosition.z);
			}
			position.z = startingPosition.z;
			position.x += static_cast<float>(Chunk::s_chunkWidth * relativeToPosition.x);
		}
	}

	void World::GenerateChunksSync(glm::vec3 startingPosition, glm::vec3 relativeToPosition)
	{
		glm::vec3 position = startingPosition;
		for (int x = 0; x < m_defaultChunkRenderCount; x++)
		{
			for (int z = 0; z < m_defaultChunkRenderCount; z++)
			{
				m_chunks.push_back(Chunk::CreateChunk(position));
				position.z += static_cast<float>(Chunk::s_chunkLength * relativeToPosition.z);
			}
			position.z = startingPosition.z;
			position.x += static_cast<float>(Chunk::s_chunkWidth * relativeToPosition.x);
		}
	}

	int32_t World::GetWorldTop()
	{
		return s_instance.WorldTop();
	}

	/*
		Instance methods
	*/

	void World::OnInit()
	{
		s_instance.OnWorldInit();
	}

	const std::vector<Ref<Chunk>>& World::GetChunks()
	{
		return s_instance.GetWorldChunks();
	}

	int32_t World::WorldTop()
	{
		return m_worldTop;
	}
}