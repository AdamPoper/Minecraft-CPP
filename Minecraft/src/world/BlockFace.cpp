#include "BlockFace.h"

namespace Mc
{
    std::array<glm::vec3, 8> BlockFace::s_positions = {
        glm::vec3(-0.5f,  0.5f,  0.5f), // 0
        glm::vec3( 0.5f,  0.5f,  0.5f), // 1
        glm::vec3( 0.5f, -0.5f,  0.5f), // 2
        glm::vec3(-0.5f, -0.5f,  0.5f), // 3
        glm::vec3(-0.5f,  0.5f, -0.5f), // 4
        glm::vec3( 0.5f,  0.5f, -0.5f), // 5
        glm::vec3( 0.5f, -0.5f, -0.5f), // 6
        glm::vec3(-0.5f, -0.5f, -0.5f), // 7
    };


    std::array<glm::vec2, 4> BlockFace::s_texCoords = {
        glm::vec2(0.0f, 0.0f), // 0
        glm::vec2(0.0f, 1.0f), // 1
        glm::vec2(1.0f, 0.0f), // 2
        glm::vec2(1.0f, 1.0f)  // 3
    };

    BlockFace::BlockFace(Texture texture, Direction direction)
	    :m_texture(texture), m_direction(direction)
    {
        InitVertexPositions();
        InitVertexTextureCoords();
    }

    void BlockFace::InitVertexPositions()
    {
        std::array<uint32_t, 4> indices;
        switch (m_direction)
        {
            case Direction::FRONT:  indices = { 0, 1, 2, 3 }; break;
            case Direction::BACK:   indices = { 4, 5, 6, 7 }; break;
            case Direction::RIGHT:  indices = { 1, 5, 6, 2 }; break;
            case Direction::LEFT:   indices = { 4, 0, 3, 7 }; break;
            case Direction::TOP:    indices = { 4, 5, 1, 0 }; break;
            case Direction::BOTTOM: indices = { 3, 2, 6, 7 }; break;
            default: MC_CONSOLE_LOG("Unknown Blockface Direction");
        }        

        for (int i = 0; i < 4; i++)
            m_vertices[i].position = s_positions[indices[i]];
    }

    void BlockFace::InitVertexTextureCoords()
    {
        glm::ivec2 atlasDimensions = TextureAtlas::GetDimensions();
        float texSize = TextureAtlas::GetTextureWidth();
        float x = 0.0f, y = 0.0f;

        switch (m_texture)
        {
            case Texture::GRASS:          x = 0.0f; y = 2.0f; break;
            case Texture::DIRT:           x = 1.0f; y = 2.0f; break;
            case Texture::STONE:          x = 2.0f; y = 1.0f; break;
            case Texture::SAND:           x = 1.0f; y = 0.0f; break;
            case Texture::WOOD_OAK_PLANK: x = 1.0f; y = 1.0f; break;
            case Texture::WOOD_OAK:       x = 0.0f; y = 1.0f; break;
            case Texture::DIRT_GRASS:     x = 2.0f; y = 2.0f; break;
            case Texture::COBBLE_STONE:   x = 0.0f; y = 0.0f; break;
            case Texture::GLASS:          x = 2.0f; y = 0.0f; break;
            default: MC_CONSOLE_LOG("Unknown Block Face Texture");
        }

        m_vertices[0].texCoords.x = (x * texSize) / atlasDimensions.x;
        m_vertices[0].texCoords.y = (y * texSize) / atlasDimensions.y;
        m_vertices[1].texCoords.x = ((x + 1) * texSize) / atlasDimensions.x;
        m_vertices[1].texCoords.y = (y * texSize) / atlasDimensions.y;
        m_vertices[2].texCoords.x = ((x + 1) * texSize) / atlasDimensions.x;
        m_vertices[2].texCoords.y = ((y + 1) * texSize) / atlasDimensions.y;
        m_vertices[3].texCoords.x = (x * texSize) / atlasDimensions.x;
        m_vertices[3].texCoords.y = ((y + 1) * texSize) / atlasDimensions.y;
    }

    const std::array<Vertex, 4>& BlockFace::GetVertices() const
    {
        return m_vertices;
    }

    Texture BlockFace::GetTexture() const
    {
        return m_texture;
    }

    void BlockFace::ChangeTexture(Texture texture)
    {
        m_texture = texture;
        InitVertexTextureCoords();
    }

    void BlockFace::SetDirection(Direction direction)
    {
        m_direction = direction;
        InitVertexPositions();
    }

    Direction BlockFace::GetDirection() const
    {
        return m_direction;
    }

    void BlockFace::Translate(glm::vec3 transform)
    {
        for (Vertex& vertex : m_vertices)
            vertex.position += transform;                
    }

    bool BlockFace::ShouldRender() const
    {
        return m_shouldRender;
    }

    void BlockFace::SetShouldRender(bool shouldRender)
    {
        m_shouldRender = shouldRender;
    }
}