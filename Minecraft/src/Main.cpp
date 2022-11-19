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
#include "world/Block.h"
#include "Renderer/Renderer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main()
{
    //Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft");

    // if (glewInit() == GLEW_OK)
    // {
    //     MC_CONSOLE_LOG("Glew Works");
    // }
    // else
    // {
    //     MC_CONSOLE_LOG("Glew Does Not Work");
    // }

    // glEnable(GL_DEPTH_TEST);
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // 
    // glm::mat4 model(1.0f);
    // 
    // TextureAtlas::Get().Create();

    Renderer::OnInit();

    std::array<Block, 2> blocks;
    blocks[0].SetBlockType(BlockType::STONE);
    blocks[0].SetPosition(glm::vec3(-2.0f, 2.0f, -2.0f));
    blocks[0].Translate(glm::vec3(1.0f, 0.0f, 1.0f));
    blocks[0].SetBlockType(BlockType::WOOD_OAK);

    blocks[1].SetBlockType(BlockType::DIRT);
    blocks[1].SetPosition(glm::vec3(3.0f, -2.0f, -5.5f));

    std::vector<Vertex> allBlockVertices;
    for (Block& block : blocks)
    {
        for (const Vertex* vertex : block.GetVertices())
        {
            allBlockVertices.push_back(*vertex);
        }
    }

    std::vector<uint32_t> blockFaceIndices;
    uint32_t maxIndex = 0;
    for (int i = 0; i < blocks.size() * Block::s_blockFacesCount; i++)
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

    Renderer::SetVertexData(allBlockVertices.data(), allBlockVertices.size());
    Renderer::SetIndexData(blockFaceIndices.data(), blockFaceIndices.size());

    // std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
    // 
    // std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(allBlockVertices.size() * sizeof(Vertex));
    // std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(blockFaceIndices.size());

    // vbo->SetData(allBlockVertices.data(), allBlockVertices.size() * sizeof(Vertex));
    // ibo->SetData(blockFaceIndices.data(), blockFaceIndices.size());
    // 
    // // vertices
    // vao->push(3, GL_FLOAT, GL_FALSE);
    // 
    // // texture coordinates
    // vao->push(2, GL_FLOAT, GL_FALSE);
    // 
    // ShaderProgram shaderProgram;
    // std::shared_ptr<Shader> vs = Shader::CreateShader<VertexShader>();
    // std::shared_ptr<Shader> fs = Shader::CreateShader<FragmentShader>();
    // 
    // shaderProgram.AttachShader(vs);
    // shaderProgram.AttachShader(fs);
    // shaderProgram.CreateShaderProgram();

    float speed = 5.0f;

    TimeStep ts;

    Window& window = *Renderer::GetWindow();

    while (window.IsOpen())
    {
        ts.stop();
        ts.start();

        if (Window::isKeyPressed(KEY_W))
            window.GetCamera().moveForward(ts);
        if (Window::isKeyPressed(KEY_S))
            window.GetCamera().moveBackward(ts);
        if (Window::isKeyPressed(KEY_A))
            window.GetCamera().strafeLeft(ts);
        if (Window::isKeyPressed(KEY_D))
            window.GetCamera().strafeRight(ts);

        Renderer::OnUpdate();

        // TextureAtlas::Get().Bind();
        // shaderProgram.SetUniform1i(TextureAtlas::Get().GetOpenGLUniformID(), 0);
        // 
        // window.getCamera().onUpdate();
        // 
        // shaderProgram.SetUniformMat4("u_projection", window.getCamera().getProjection());
        // shaderProgram.SetUniformMat4("u_view", window.getCamera().getView());
        // shaderProgram.SetUniformMat4("u_model", glm::mat4(1.0f));
        // 
        // shaderProgram.Bind();
        // vao->Bind();
        // ibo->Bind();
        // 
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glClearColor(0.3f, 0.5f, 0.9f, 1.0f);
        // 
        // glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
        // 
        // uint32_t error = glGetError();
        // if (error)
        // {
        //     MC_CONSOLE_LOG_ERROR(error);
        // }
        // 
        // window.OnUpdate();

    }
}