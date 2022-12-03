#include "World.h"

namespace Mc
{
	World World::s_instance;

	std::mutex World::s_chunksMutex;

	World::World()
	{
		m_chunks.reserve(m_defaultChunkRenderCount * m_defaultChunkRenderCount);
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
		
		GenerateChunksAsync(generateChunkAsync, startingPosition, glm::vec3( 1.0f, 0.0f,  1.0f));
		GenerateChunksAsync(generateChunkAsync, startingPosition, glm::vec3( 1.0f, 0.0f, -1.0f));
		GenerateChunksAsync(generateChunkAsync, startingPosition, glm::vec3(-1.0f, 0.0f,  1.0f));
		GenerateChunksAsync(generateChunkAsync, startingPosition, glm::vec3(-1.0f, 0.0f, -1.0f));
		
		for (const std::future<void>& future : m_chunkFutures) future.wait();

#else

		GenerateChunksSync(startingPosition, glm::vec3( 1.0f, 0.0f,  1.0f));
		GenerateChunksSync(startingPosition, glm::vec3( 1.0f, 0.0f, -1.0f));
		GenerateChunksSync(startingPosition, glm::vec3(-1.0f, 0.0f,  1.0f));
		GenerateChunksSync(startingPosition, glm::vec3(-1.0f, 0.0f, -1.0f));

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
		for (int x = 0; x < 12 / 4; x++)
		{
			for (int z = 0; z < 12 / 4; z++)
			{
				m_chunkFutures.push_back(std::async(std::launch::async, generateChunkCallback, &m_chunks, startingPosition));
				startingPosition.z += static_cast<float>(Chunk::s_chunkLength * relativeToPosition.z);
			}
			startingPosition.z = 0.0f;
			startingPosition.x += static_cast<float>(Chunk::s_chunkWidth * relativeToPosition.x);
		}
	}

	void World::GenerateChunksSync(glm::vec3 startingPosition, glm::vec3 relativeToPosition)
	{
		for (int x = 0; x < 12 / 4; x++)
		{
			for (int z = 0; z < 12 / 4; z++)
			{
				m_chunks.push_back(Chunk::CreateChunk(startingPosition));
				startingPosition.z += static_cast<float>(Chunk::s_chunkLength * relativeToPosition.z);
			}
			startingPosition.z = 0.0f;
			startingPosition.x += static_cast<float>(Chunk::s_chunkWidth * relativeToPosition.x);
		}
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
}