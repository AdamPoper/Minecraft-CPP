#pragma once

#include <vector>

#include "Chunk.h"

namespace Mc
{
	class World
	{
	public:

		static const World& Get();

		static void OnInit();

		static const std::vector<Chunk>& GetChunks();

	private:

		World();

		World(const World&) = delete;

		void OnWorldInit();

		const std::vector<Chunk>& GetWorldChunks() const;

		uint32_t GetCountChunks() const;

		void GenerateChunks(glm::vec3 relativeToWorldCenter, glm::vec3 startingPosition);

	private:

		static World s_instance;

	private:

		std::vector<Chunk> m_chunks;
		
		int32_t m_worldTop = 128;
		int32_t m_worldBottom = -127;
	};
}