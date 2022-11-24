#include "World.h"

namespace Mc
{
	World World::s_instance;

	World::World()
	{
		m_blocks.reserve(25);
	}

	void World::OnWorldInit()
	{
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int x = 0; x < 5; x++)
		{
			for (int z = 0; z < 5; z++)
			{
				position.z = z;
				m_blocks.emplace_back(BlockType::DIRT, position);
			}
			position.x = x;
		}
	}

	const std::vector<Block>& World::GetWorldBlocks() const
	{
		return m_blocks;
	}

	/*
		Instance methods
	*/

	void World::OnInit()
	{
		s_instance.OnWorldInit();
	}

	const std::vector<Block>& World::GetBlocks()
	{
		return s_instance.GetWorldBlocks();
	}
}