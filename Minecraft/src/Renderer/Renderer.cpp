#pragma once

#include "Renderer.h"

Renderer Renderer::s_instance;

Renderer::Renderer()
{
    m_model = glm::mat4(1.0f);
}

void Renderer::OnRendererInit()
{
    m_window = std::make_shared<Window>(m_defaultWindowWidth, m_defaultWindowHeight, "MineCraft");

    if (glewInit() == GLEW_OK)
    {
        MC_CONSOLE_LOG("Glew Works");
    }
    else
    {
        MC_CONSOLE_LOG("Glew Does Not Work");
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 800);

    TextureAtlas::Get().Create();
    m_vertexArray = std::make_shared<VertexArray>();
    m_vertexBuffer = std::make_shared<VertexBuffer>();
    m_indexBuffer = std::make_shared<IndexBuffer>();
    m_shaderProgram = std::make_shared<ShaderProgram>();

    m_vertexArray->push(3, GL_FLOAT, GL_FALSE);
    m_vertexArray->push(2, GL_FLOAT, GL_FALSE);

    std::shared_ptr<Shader> vertexShader = Shader::CreateShader<VertexShader>();
    std::shared_ptr<Shader> fragmentShader = Shader::CreateShader<FragmentShader>();

    m_shaderProgram->AttachShader(vertexShader);
    m_shaderProgram->AttachShader(fragmentShader);
    m_shaderProgram->CreateShaderProgram();
}

void Renderer::OnRendererUpdate()
{
    TextureAtlas::Get().Bind();
    m_shaderProgram->SetUniform1i(TextureAtlas::Get().GetOpenGLUniformID(), 0);
    
    m_window->GetCamera().onUpdate();

    m_shaderProgram->SetUniformMat4("u_projection", m_window->GetCamera().getProjection());
    m_shaderProgram->SetUniformMat4("u_view", m_window->GetCamera().getView());
    m_shaderProgram->SetUniformMat4("u_model", m_model);

    m_shaderProgram->Bind();
    m_vertexArray->Bind();
    m_indexBuffer->Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3f, 0.5f, 0.9f, 1.0f);

    glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

    uint32_t error = glGetError();
    if (error)
    {
        MC_CONSOLE_LOG_ERROR(error);
    }

    m_window->OnUpdate();
}

void Renderer::SetVertexBufferData(Vertex* vertices, size_t size)
{
    m_vertexBuffer->SetData(vertices, size);
}

void Renderer::SetIndexBufferData(uint32_t* indices, size_t size)
{
    m_indexBuffer->SetData(indices, size);
}

std::shared_ptr<Window> Renderer::GetRenderingWindow()
{
    return m_window;
}

std::shared_ptr<Camera> Renderer::GetWindowCamera()
{
    return std::make_shared<Camera>(m_window->GetCamera());
}

/*
    Instance Methods
*/

Renderer& Renderer::Get() { return s_instance; }

void Renderer::SetVertexData(Vertex* vertices, size_t size)
{
    s_instance.SetVertexBufferData(vertices, size);
}

void Renderer::SetIndexData(uint32_t* indices, size_t size)
{
    s_instance.SetIndexBufferData(indices, size);
}

void Renderer::OnUpdate()
{
    s_instance.OnRendererUpdate();
}

std::shared_ptr<Window> Renderer::GetWindow()
{
    return s_instance.GetRenderingWindow();
}

std::shared_ptr<Camera> Renderer::GetCamera()
{
    return s_instance.GetCamera();
}

void Renderer::OnInit() { s_instance.OnRendererInit(); }