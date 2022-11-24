#pragma once

#include "Renderer.h"

Renderer Renderer::s_instance;

Renderer::Renderer()
{
}

void Renderer::OnRendererInit()
{
    m_window = CreateRef<Window>(m_windowWidth, m_windowHeight, "Minecraft");

    if (glewInit() == GLEW_OK)
    {
        MC_CONSOLE_LOG("Glew Works");
    }
    else
    {
        MC_CONSOLE_LOG("Glew Does Not Work");
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, m_windowWidth, m_windowHeight);

    TextureAtlas::Create(m_textureAtlasFilePath, m_countTextureAtlasTextureWidth, m_countTextureAtlasTextureHeight);
    m_vertexArray   = CreateRef<VertexArray>();
    m_vertexBuffer  = CreateRef<VertexBuffer>();
    m_indexBuffer   = CreateRef<IndexBuffer>();
    m_shaderProgram = CreateRef<ShaderProgram>();

    m_vertexArray->push(3, GL_FLOAT, GL_FALSE);
    m_vertexArray->push(2, GL_FLOAT, GL_FALSE);

    Scope<Shader> vertexShader = Shader::CreateShader<VertexShader>();
    Scope<Shader> fragmentShader = Shader::CreateShader<FragmentShader>();

    m_shaderProgram->AttachShader(vertexShader);
    m_shaderProgram->AttachShader(fragmentShader);
    m_shaderProgram->CreateShaderProgram();
}

void Renderer::OnRendererUpdate()
{
    m_window->GetCamera().onUpdate();

    m_shaderProgram->SetUniform1i(TextureAtlas::GetOpenGLUniformID(), 0);
    m_shaderProgram->SetUniformMat4("u_projection", m_window->GetCamera().getProjection());
    m_shaderProgram->SetUniformMat4("u_view", m_window->GetCamera().getView());
    m_shaderProgram->SetUniformMat4("u_model", glm::mat4(1.0f));

    TextureAtlas::Get().Bind();
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

Ref<Window> Renderer::GetRenderingWindow()
{
    return m_window;
}

Ref<Camera> Renderer::GetWindowCamera()
{
    return CreateRef<Camera>(m_window->GetCamera());
}

void Renderer::SetRendererTextureAtlasFilePath(const std::string& filepath, uint32_t countWidth, uint32_t countHeight)
{
    m_textureAtlasFilePath = filepath;
    m_countTextureAtlasTextureWidth = countWidth;
    m_countTextureAtlasTextureHeight = countHeight;
}

void Renderer::SetRendererWindowViewDimensions(float width, float height)
{
    m_windowWidth = width;
    m_windowHeight = height;
}

/*
    Instance Methods
*/

const Renderer& Renderer::Get() { return s_instance; }

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

Ref<Window> Renderer::GetWindow()
{
    return s_instance.GetRenderingWindow();
}

Ref<Camera> Renderer::GetCamera()
{
    return s_instance.GetCamera();
}

void Renderer::OnInit() { s_instance.OnRendererInit(); }

void Renderer::SetTextureAtlasFilePath(const std::string& filepath, uint32_t countWidth, uint32_t countHeight)
{
    s_instance.SetRendererTextureAtlasFilePath(filepath, countWidth, countHeight);
}

void Renderer::SetWindowViewDimensions(float width, float height)
{
    s_instance.SetRendererWindowViewDimensions(width, height);
}