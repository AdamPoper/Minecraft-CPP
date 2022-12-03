#include "World.h"

namespace Mc
{
	World World::s_instance;

	World::World()
	{
		m_chunks.reserve(GetCountChunks());
	}

	void World::OnWorldInit()
	{
		glm::vec3 position(0.0f, m_worldBottom, 0.0f);


		m_chunks.emplace_back(position);

		//for (int x = 0; x < m_chunksWidth / 2; x++)
		//{
		//	for (int z = 1; z <= m_chunksLength / 2; z++)
		//	{
		//		for (int y = 1; y <= m_chunksHeight; y++)
		//		{
		//			position = glm::vec3(
		//				static_cast<float>(Chunk::s_chunkWidth) * static_cast<float>(x),
		//				static_cast<float>(Chunk::s_chunkHeight) * static_cast<float>(-y),
		//				static_cast<float>(Chunk::s_chunkLength) * static_cast<float>(-z));
		//			m_chunks.emplace_back(position);
		//		}
		//	}
		//}
		//
		//for (int x = 1; x <= m_chunksWidth / 2; x++)
		//{
		//	for (int z = 0; z < m_chunksLength / 2; z++)
		//	{
		//		for (int y = 1; y <= m_chunksHeight; y++)
		//		{
		//			position = glm::vec3(
		//				static_cast<float>(Chunk::s_chunkWidth) * static_cast<float>(-x),
		//				static_cast<float>(Chunk::s_chunkHeight) * static_cast<float>(-y),
		//				static_cast<float>(Chunk::s_chunkLength) * static_cast<float>(z));
		//			m_chunks.emplace_back(position);
		//		}
		//	}
		//}
		//
		//for (int x = 1; x <= m_chunksWidth / 2; x++)
		//{
		//	for (int z = 1; z <= m_chunksLength / 2; z++)
		//	{
		//		for (int y = 1; y <= m_chunksHeight; y++)
		//		{
		//			position = glm::vec3(
		//				static_cast<float>(Chunk::s_chunkWidth) * static_cast<float>(-x),
		//				static_cast<float>(Chunk::s_chunkHeight) * static_cast<float>(-y),
		//				static_cast<float>(Chunk::s_chunkLength) * static_cast<float>(-z));
		//			m_chunks.emplace_back(position);
		//		}
		//	}
		//}
	}

	const std::vector<Chunk>& World::GetWorldChunks() const
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

	void World::GenerateChunks(glm::vec3 relativeToWorldCenter, glm::vec3 startingPosition)
	{
		
	}

	/*
		Instance methods
	*/

	void World::OnInit()
	{
		s_instance.OnWorldInit();
	}

	const std::vector<Chunk>& World::GetChunks()
	{
		return s_instance.GetWorldChunks();
	}
}