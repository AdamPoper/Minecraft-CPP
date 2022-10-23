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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main(void)
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

    std::array<glm::vec3, 4> positions = {
        glm::vec3(-0.5f,  0.5f, -0.5f), // 0
        glm::vec3(0.5f,  0.5f, -0.5f), // 1
        glm::vec3(0.5f, -0.5f, -0.5f), // 2

        glm::vec3(-0.5f, -0.5f, -0.5f), // 3
        //glm::vec3(-0.5f, -0.5f,  0.5f), // 4
        //glm::vec3( 0.5f, -0.5f,  0.5f), // 5
        //glm::vec3( 0.5f,  0.5f,  0.5f), // 6
        //glm::vec3(-0.5f,  0.5f,  0.5f), // 7
    };

    std::array<Vertex, 4> vertices = {
        Vertex(positions[0], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),
        Vertex(positions[1], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),
        Vertex(positions[2], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),
        Vertex(positions[3], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),
       // Vertex(positions[0], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),
       // Vertex(positions[2], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),
       // Vertex(positions[3], glm::vec4(1.0f, 0.6f, 0.0f, 1.0f)),

        //Vertex(positions[2], glm::vec4(1.0f, 0.0f, 0.6f, 1.0f)),
        //Vertex(positions[3], glm::vec4(1.0f, 0.0f, 0.6f, 1.0f)),
        //Vertex(positions[4], glm::vec4(1.0f, 0.0f, 0.6f, 1.0f)),
        //Vertex(positions[2], glm::vec4(1.0f, 0.0f, 0.6f, 1.0f)),
        //Vertex(positions[4], glm::vec4(1.0f, 0.0f, 0.6f, 1.0f)),
        //Vertex(positions[5], glm::vec4(1.0f, 0.0f, 0.6f, 1.0f)),
        //
        //Vertex(positions[1], glm::vec4(1.0f, 0.5f, 0.3f, 1.0f)),
        //Vertex(positions[2], glm::vec4(1.0f, 0.5f, 0.3f, 1.0f)),
        //Vertex(positions[5], glm::vec4(1.0f, 0.5f, 0.3f, 1.0f)),
        //Vertex(positions[1], glm::vec4(1.0f, 0.5f, 0.3f, 1.0f)),
        //Vertex(positions[5], glm::vec4(1.0f, 0.5f, 0.3f, 1.0f)),
        //Vertex(positions[6], glm::vec4(1.0f, 0.5f, 0.3f, 1.0f)),
        //
        //Vertex(positions[4], glm::vec4(2.0f, 0.3f, 0.9f, 1.0f)),
        //Vertex(positions[5], glm::vec4(2.0f, 0.3f, 0.9f, 1.0f)),
        //Vertex(positions[6], glm::vec4(2.0f, 0.3f, 0.9f, 1.0f)),
        //Vertex(positions[4], glm::vec4(2.0f, 0.3f, 0.9f, 1.0f)),
        //Vertex(positions[6], glm::vec4(2.0f, 0.3f, 0.9f, 1.0f)),
        //Vertex(positions[7], glm::vec4(2.0f, 0.3f, 0.9f, 1.0f)),
        //
        //Vertex(positions[0], glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)),
        //Vertex(positions[3], glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)),
        //Vertex(positions[4], glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)),
        //Vertex(positions[0], glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)),
        //Vertex(positions[4], glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)),
        //Vertex(positions[7], glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)),
        //
        //Vertex(positions[0], glm::vec4(0.2f, 0.9f, 0.5f, 1.0f)),
        //Vertex(positions[1], glm::vec4(0.2f, 0.9f, 0.5f, 1.0f)),
        //Vertex(positions[6], glm::vec4(0.2f, 0.9f, 0.5f, 1.0f)),
        //Vertex(positions[0], glm::vec4(0.2f, 0.9f, 0.5f, 1.0f)),
        //Vertex(positions[6], glm::vec4(0.2f, 0.9f, 0.5f, 1.0f)),
        //Vertex(positions[7], glm::vec4(0.2f, 0.9f, 0.5f, 1.0f)),
    };

    std::array<uint32_t, 6> indices = {
         0, 1, 2,
         0, 2, 3,
    };

    ShaderProgram shaderProgram;
    VertexShader vs = Shader::CreateShader<VertexShader>();
    FragmentShader fs = Shader::CreateShader<FragmentShader>();
    shaderProgram.AttachShader(vs);
    shaderProgram.AttachShader(fs);
    shaderProgram.CreateShaderProgram();

    VertexArray vao;

    VertexBuffer vbo(vertices.data(), vertices.size());
    IndexBuffer ibo(indices.data(), indices.size());

    // uint32_t vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (const void*)vertices.data(), GL_STATIC_DRAW);

    // uint32_t ibo;
    // glGenBuffers(1, &ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), (const void*)indices.data(), GL_STATIC_DRAW);

    // vertices
    vao.push(3, GL_FLOAT, GL_FALSE);

    // color
    vao.push(4, GL_FLOAT, GL_FALSE);

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

        window.getCamera().onUpdate();

        shaderProgram.SetUniformMat4("u_projection", window.getCamera().getProjection());
        shaderProgram.SetUniformMat4("u_view", window.getCamera().getView());
        shaderProgram.SetUniformMat4("u_model", model);

        shaderProgram.Bind();
        vao.Bind();
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        ibo.Bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.5f, 0.9f, 1.0f);

        glDrawElements(GL_TRIANGLES, ibo.GetSize(), GL_UNSIGNED_INT, nullptr);
        
        uint32_t error = glGetError();
        if (error)
        {
            std::cout << error << std::endl;
        }

        window.OnUpdate();
    }
}