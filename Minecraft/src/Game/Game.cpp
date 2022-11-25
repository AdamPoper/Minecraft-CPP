#include "Game.h"

Game Game::s_gameInstance;

void Game::OnGameInit()
{
	Renderer::SetTextureAtlasFilePath("res/textures/atlas.png", 3, 3);
	Renderer::SetWindowViewDimensions(1920.0f, 1080.0f);
	Renderer::OnInit();

    m_windowHandle = Renderer::GetWindow();

	Mc::World::OnInit();

    const std::vector<Mc::Block>& blocks = Mc::World::GetBlocks();

    std::vector<Vertex> allBlockVertices;
    for (const Mc::Block& block : blocks)
    {
        for (const Vertex* vertex : block.GetVertices())
        {
            allBlockVertices.push_back(*vertex);
        }
    }

    std::vector<uint32_t> blockFaceIndices;
    uint32_t maxIndex = 0;
    for (int i = 0; i < blocks.size() * Mc::Block::s_blockFacesCount; i++)
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
}

void Game::Run()
{
    TimeStep ts;

    while (m_windowHandle->IsOpen())
    {
        ts.stop();
        ts.start();

        if (Window::IsKeyPressed(KEY_W))
            m_windowHandle->GetCamera().moveForward(ts);
        if (Window::IsKeyPressed(KEY_S))
            m_windowHandle->GetCamera().moveBackward(ts);
        if (Window::IsKeyPressed(KEY_A))
            m_windowHandle->GetCamera().strafeLeft(ts);
        if (Window::IsKeyPressed(KEY_D))
            m_windowHandle->GetCamera().strafeRight(ts);

        Renderer::OnUpdate();
    }
}

/*
	Instance methods
*/

void Game::OnInit()
{
	s_gameInstance.OnGameInit();
}

void Game::OnGameRun()
{
    s_gameInstance.Run();
}