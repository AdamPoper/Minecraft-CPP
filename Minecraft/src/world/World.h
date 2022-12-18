#pragma once

#include "Chunk.h"
#include "../Util/TimeStep.h"
#include "../Util/PerlinNoise.h"

#include <vector>
#include <future>
#include <functional>

namespace Mc
{
	class World
	{
	public:

		static const World& Get();

		static void OnInit();

		static const std::vector<Ref<Chunk>>& GetChunks();

	private:

		World();

		World(const World&) = delete;

		void OnWorldInit();

		const std::vector<Ref<Chunk>>& GetWorldChunks() const;

		uint32_t GetCountChunks() const;

		int32_t WorldTop();

		void GenerateChunksAsync(
			std::function<void(std::vector<Ref<Chunk>>*, glm::vec3)> callback,
			glm::vec3 startingPosition,
			glm::vec3 relativeToWorldCenter);

		void GenerateChunksSync(
			glm::vec3 startingPosition,
			glm::vec3 relativeToWorldCenter);

	public:

		static int32_t GetWorldTop();

	private:

		static World s_instance;

		static std::mutex s_chunksMutex;

	private:

		Ref<PerlinNoise> m_terrainNoise;

		std::vector<Ref<Chunk>> m_chunks;

		std::vector<std::future<void>> m_chunkFutures;

		int32_t m_worldTop = 64;

		int32_t m_worldBottom = -63;

		const uint32_t m_defaultChunkRenderCount = 8;
	};
}