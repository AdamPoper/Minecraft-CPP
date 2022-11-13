#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

#include "Renderer/Window.h"
#include "Logger/Logger.h"
#include "Renderer/Shader.h"
#include "Util/Vertex.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/TextureAtlas.h"
#include "world/BlockFace.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main()
{
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft");

    if (glewInit() == GLEW_OK)
    {
        MC_CONSOLE_LOG("Glew Works");
    }
    else
    {
        MC_CONSOLE_LOG("Glew Does Not Work");
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glm::mat4 model(1.0f);

    std::array<glm::vec3, 8> positions = {
        glm::vec3(-0.5f,  0.5f,  0.5f), // 0
        glm::vec3( 0.5f,  0.5f,  0.5f), // 1
        glm::vec3( 0.5f, -0.5f,  0.5f), // 2
        glm::vec3(-0.5f, -0.5f,  0.5f), // 3
        glm::vec3(-0.5f,  0.5f, -0.5f), // 4
        glm::vec3( 0.5f,  0.5f, -0.5f), // 5
        glm::vec3( 0.5f, -0.5f, -0.5f), // 6
        glm::vec3(-0.5f, -0.5f, -0.5f), // 7
    };

    std::array<glm::vec2, 4> texCoords = {
        glm::vec2(0.0f, 0.0f), // 0
        glm::vec2(0.0f, 1.0f), // 1
        glm::vec2(1.0f, 0.0f), // 2
        glm::vec2(1.0f, 1.0f)  // 3
    };

    std::array<Vertex, 24> vertices = {
        // front
        Vertex(positions[0], texCoords[1]), // 0
        Vertex(positions[1], texCoords[3]), // 1
        Vertex(positions[2], texCoords[2]), // 2
        Vertex(positions[3], texCoords[0]), // 3

        // back
        Vertex(positions[4], texCoords[3]), // 4
        Vertex(positions[5], texCoords[1]), // 5
        Vertex(positions[6], texCoords[0]), // 6
        Vertex(positions[7], texCoords[2]), // 7

        // right
        Vertex(positions[1], texCoords[1]), // 8
        Vertex(positions[2], texCoords[0]), // 9
        Vertex(positions[5], texCoords[3]), // 10
        Vertex(positions[6], texCoords[2]), // 11

        // left
        Vertex(positions[4], texCoords[1]), // 12
        Vertex(positions[0], texCoords[3]), // 13
        Vertex(positions[3], texCoords[2]), // 14
        Vertex(positions[7], texCoords[0]), // 15

        // bottom
        Vertex(positions[3], texCoords[0]), // 16
        Vertex(positions[2], texCoords[2]), // 17
        Vertex(positions[7], texCoords[1]), // 18
        Vertex(positions[6], texCoords[3]), // 19
        
        // top
        Vertex(positions[0], texCoords[0]), // 20
        Vertex(positions[1], texCoords[2]), // 21
        Vertex(positions[4], texCoords[1]), // 22
        Vertex(positions[5], texCoords[3]), // 23  
    };

    std::array<uint32_t, 36> indices = {
         0, 1, 2, // front
         0, 2, 3,
         
         4, 5, 6, // back
         4, 6, 7,

         8, 9, 10, // right
         9, 10, 11,

         12, 13, 14, // left
         12, 14, 15,

         16, 17, 18, // bottom
         17, 18, 19,

         20, 21, 22, // top
         21, 22, 23
    };

    TextureAtlas::Get().Create();

    std::vector<BlockFace> blockFaces;
    blockFaces.push_back(BlockFace(Texture::COBBLE_STONE, Direction::FRONT));
    blockFaces.push_back(BlockFace(Texture::STONE, Direction::BACK));
    blockFaces.push_back(BlockFace(Texture::DIRT_GRASS, Direction::RIGHT));
    blockFaces.push_back(BlockFace(Texture::SAND, Direction::LEFT));
    blockFaces.push_back(BlockFace(Texture::WOOD_OAK, Direction::TOP));
    blockFaces.push_back(BlockFace(Texture::WOOD_OAK_PLANK, Direction::BOTTOM));


    std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();

    std::vector<Vertex> blockFaceVertices;
    for (const BlockFace& blockFace : blockFaces)
    {
        for (const Vertex& vertex : blockFace.GetVertices())
        {
            blockFaceVertices.push_back(vertex);
        }
    }

    std::vector<uint32_t> blockFaceIndices;
    uint32_t maxIndex = 0;
    for (int i = 0; i < blockFaces.size(); i++)
    {
        uint32_t index0 = maxIndex; maxIndex++;
        uint32_t index1 = maxIndex; maxIndex++;
        uint32_t index2 = maxIndex; maxIndex++;
        uint32_t index3 = maxIndex; maxIndex++;

        blockFaceIndices.push_back(index0);
        blockFaceIndices.push_back(index1);
        blockFaceIndices.push_back(index2);
        blockFaceIndices.push_back(index0);
        blockFaceIndices.push_back(index2);
        blockFaceIndices.push_back(index3);
    }

    std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(blockFaceVertices.size() * sizeof(Vertex));
    std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(blockFaceIndices.size());

    vbo->SetData(blockFaceVertices.data(), blockFaceVertices.size() * sizeof(Vertex));
    ibo->SetData(blockFaceIndices.data(), blockFaceIndices.size());

    // vertices
    vao->push(3, GL_FLOAT, GL_FALSE);

    // texture coordinates
    vao->push(2, GL_FLOAT, GL_FALSE);

    ShaderProgram shaderProgram;
    std::shared_ptr<Shader> vs = Shader::CreateShader<VertexShader>();
    std::shared_ptr<Shader> fs = Shader::CreateShader<FragmentShader>();

    shaderProgram.AttachShader(vs);
    shaderProgram.AttachShader(fs);
    shaderProgram.CreateShaderProgram();

    float speed = 5.0f;

    TimeStep ts;

    while (window.isOpen())
    {
        ts.stop();
        ts.start();

        if (Window::isKeyPressed(KEY_W))
            window.getCamera().moveForward(ts);
        if (Window::isKeyPressed(KEY_S))
            window.getCamera().moveBackward(ts);
        if (Window::isKeyPressed(KEY_A))
            window.getCamera().strafeLeft(ts);
        if (Window::isKeyPressed(KEY_D))
            window.getCamera().strafeRight(ts);

        TextureAtlas::Get().Bind();
        shaderProgram.SetUniform1i(TextureAtlas::Get().GetOpenGLUniformID(), 0);

        window.getCamera().onUpdate();

        shaderProgram.SetUniformMat4("u_projection", window.getCamera().getProjection());
        shaderProgram.SetUniformMat4("u_view", window.getCamera().getView());
        shaderProgram.SetUniformMat4("u_model", model);

        shaderProgram.Bind();
        vao->Bind();
        ibo->Bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.5f, 0.9f, 1.0f);

        glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
        
        uint32_t error = glGetError();
        if (error)
        {
            MC_CONSOLE_LOG_ERROR(error);
        }

        window.OnUpdate();
    }
}