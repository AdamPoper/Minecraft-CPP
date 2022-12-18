#include "Block.h"

namespace Mc
{
	Block::Block() :
		m_blockType(BlockType::AIR),
		m_position()
	{
		InitBlockFaceDirections();
		InitBlockFaceTextures();
		SetBlockFaceVertices();
	}

	Block::Block(BlockType blockType) :
		m_blockType(blockType),
		m_position()
	{
		InitBlockFaceDirections();
		InitBlockFaceTextures();
		SetBlockFaceVertices();
	}

	Block::Block(BlockType blockType, glm::vec3 position) :
		m_blockType(blockType),
		m_position(position)
	{
		InitBlockFaceDirections();
		InitBlockFaceTextures();
		SetBlockFaceVertices();
		SetPosition(m_position);
	}

	Block::Block(const Block& block)
	{
		InitBlockFaceDirections();
		SetPosition(block.GetPosition());
		SetBlockType(block.GetBlockType());
		SetBlockFaceVertices();
	}

	Block::Block(Block&& block) noexcept :
		m_blockFaces(std::move(block.m_blockFaces)),
		m_position(std::move(block.m_position))
	{
		SetBlockType(block.m_blockType);
		SetBlockFaceVertices();
	}

	bool Block::operator<(const Block& block) { return true; }

	void Block::InitBlockFaceTextures()
	{
		switch (m_blockType)
		{
			case BlockType::WOOD_OAK_PLANK:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::WOOD_OAK_PLANK);
			}
			break;
			case BlockType::WOOD_OAK:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::WOOD_OAK);
			}
			break;
			case BlockType::STONE:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::STONE);
			}
			break;
			case BlockType::COBBLE_STONE:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::COBBLE_STONE);
			}
			break;
			case BlockType::DIRT:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::DIRT);
			}
			break;
			case BlockType::DIRT_GRASS:
			{
				for (BlockFace& blockFace : m_blockFaces)
				{
					if (blockFace.GetDirection() == Direction::TOP)
					{
						blockFace.ChangeTexture(Texture::GRASS);
					}
					else if (blockFace.GetDirection() == Direction::BOTTOM)
					{
						blockFace.ChangeTexture(Texture::DIRT);
					}
					else
					{
						blockFace.ChangeTexture(Texture::DIRT_GRASS);
					}
				}
			}
			break;
			case BlockType::SAND:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::SAND);
			}
			case BlockType::GLASS:
			{
				for (BlockFace& blockFace : m_blockFaces)
					blockFace.ChangeTexture(Texture::GLASS);
			}
			break;
			case BlockType::AIR: break;
			default: MC_CONSOLE_LOG("Unknown Block Type");
		}
	}

	const std::array<const Vertex*, Block::s_vertexCount>& Block::GetVertices() const
	{
		return m_blockFaceVertices;
	}

	const std::vector<const Vertex*>& Block::CreateMesh()
	{
		for (BlockFace& blockFace : m_blockFaces)
		{
			if (blockFace.ShouldRender())
			{
				for (const Vertex& vertex : blockFace.GetVertices())
				{
					m_vertexMesh.push_back(&vertex);
				}
			}
		}
		return m_vertexMesh;
	}

	BlockType Block::GetBlockType() const
	{
		return m_blockType;
	}

	const std::array<BlockFace, Block::s_blockFacesCount>& Block::GetBlockFaces() const
	{
		return m_blockFaces;
	}

	glm::vec3 Block::GetPosition() const
	{
		return m_position;
	}

	void Block::SetBlockType(BlockType blockType)
	{
		m_blockType = blockType;
		InitBlockFaceTextures();
	}

	void Block::SetBlockFaceVertices()
	{
		uint32_t index = 0;
		for (BlockFace& blockFace : m_blockFaces)
		{
			for (const Vertex& vertex : blockFace.GetVertices())
			{
				m_blockFaceVertices[index] = &vertex;
				index++;
			}
		}
	}

	void Block::InitBlockFaceDirections()
	{
		m_blockFaces[0].SetDirection(Direction::FRONT);
		m_blockFaces[1].SetDirection(Direction::BACK);
		m_blockFaces[2].SetDirection(Direction::RIGHT);
		m_blockFaces[3].SetDirection(Direction::LEFT);
		m_blockFaces[4].SetDirection(Direction::TOP);
		m_blockFaces[5].SetDirection(Direction::BOTTOM);

		m_blockFaceDirections.insert(std::pair<Direction, BlockFace*>(Direction::FRONT,  &m_blockFaces[0]));
		m_blockFaceDirections.insert(std::pair<Direction, BlockFace*>(Direction::BACK,   &m_blockFaces[1]));
		m_blockFaceDirections.insert(std::pair<Direction, BlockFace*>(Direction::RIGHT,  &m_blockFaces[2]));
		m_blockFaceDirections.insert(std::pair<Direction, BlockFace*>(Direction::LEFT,   &m_blockFaces[3]));
		m_blockFaceDirections.insert(std::pair<Direction, BlockFace*>(Direction::TOP,    &m_blockFaces[4]));
		m_blockFaceDirections.insert(std::pair<Direction, BlockFace*>(Direction::BOTTOM, &m_blockFaces[5]));
	}

	void Block::SetPosition(glm::vec3 pos)
	{
		m_position = pos;
		for (BlockFace& blockFace : m_blockFaces)
		{
			if (blockFace.HavePositionsChanged())
			{
				blockFace.ResetPositions();
			}
			blockFace.Translate(m_position);
		}
	}

	void Block::Translate(glm::vec3 transform)
	{
		m_position += transform;
		for (BlockFace& blockFace : m_blockFaces)
			blockFace.Translate(transform);
	}

	void Block::SetBlockFaceToRender(Direction dir)
	{
		BlockFace* blockFace = GetBlockFaceByDirection(dir);
		if (blockFace != nullptr)
		{
			blockFace->SetShouldRender(true);
		}
	}

	BlockFace* Block::GetBlockFaceByDirection(Direction dir)
	{
		auto iter = m_blockFaceDirections.find(dir);
		if (iter != m_blockFaceDirections.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	const BlockFace* Block::GetBlockFaceByDirection(Direction dir) const
	{
		return GetBlockFaceByDirection(dir);
	}
}