#pragma once

#include <vector>

#include "Block.h"

namespace Mc
{
	class World
	{
	public:

		static const World& Get();

		static void OnInit();

		static const std::vector<Block>& GetBlocks();

	private:

		World();

		World(const World&) = delete;

	private:

		void OnWorldInit();

		const std::vector<Block>& GetWorldBlocks() const;

	private:

		static World s_instance;

	private:

		// temporary
		std::vector<Block> m_blocks;
	};
}