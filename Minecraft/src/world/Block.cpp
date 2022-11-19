#include "Block.h"

Block::Block()
	: m_blockType(BlockType::AIR), m_position()
{
	InitBlockFaceDirections();
	InitBlockFaceTextures();
	SetBlockFaceVertices();
}

Block::Block(BlockType blockType)
	: m_blockType(blockType), m_position()
{
	InitBlockFaceDirections();
	InitBlockFaceTextures();
	SetBlockFaceVertices();
}

Block::Block(const Block& block)
{
	InitBlockFaceDirections();
	SetPosition(block.GetPosition());
	SetBlockType(block.GetBlockType());
	SetBlockFaceVertices();
}

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
				blockFace.ChangeTexture(Texture::DIRT_GRASS);
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
}

void Block::SetPosition(glm::vec3 position)
{
	m_position = position;
	for (BlockFace& blockFace : m_blockFaces)
	{
		glm::vec3 avg = glm::vec3(0.0f, 0.0f, 0.0f);
		for (const Vertex& vertex : blockFace.GetVertices())
		{
			avg.x += vertex.position.x;
			avg.y += vertex.position.y;
			avg.z += vertex.position.z;
		}
		avg.x /= 2.0f;
		avg.y /= 2.0f;
		avg.z /= 2.0f;
		glm::vec3 transform = m_position - avg;
		blockFace.Translate(transform);
	}
}

void Block::Translate(glm::vec3 transform)
{
	m_position += transform;
	for (BlockFace& blockFace : m_blockFaces)
		blockFace.Translate(transform);
}