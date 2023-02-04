#include "Game.h"

Game Game::s_gameInstance;

void Game::OnGameInit()
{
	Renderer::SetTextureAtlasFilePath("res/textures/atlas.png", 3, 3);
	Renderer::SetWindowViewDimensions(1920.0f, 1080.0f);
	Renderer::OnInit();

    m_windowHandle = Renderer::GetWindow();
    m_player = CreateRef<Player>();
    m_player->SetCamera(m_windowHandle->GetCamera());
    m_player->SetSpeed(m_playerSpeed);

    MC_PROFILE_START("World Init");
	Mc::World::OnInit();
    MC_PROFILE_END(Profiler::TimeFrame::SECONDS);

    m_player->TranslatePlayer(glm::vec3(0.0f, Mc::World::GetWorldTop(), 0.0f));

    const std::vector<Ref<Mc::Chunk>>& chunks = Mc::World::GetChunks();

    std::vector<Vertex> allBlockVertices;
    
    MC_PROFILE_START("Creating World Mesh");

    for (const Ref<Mc::Chunk>& chunk : chunks)
    {
        for (Mc::Block& block : chunk->GetBlocks())
        {
            if (block.GetBlockType() != Mc::BlockType::AIR)
            {
                for (const Vertex* vertex : block.CreateMesh())
                {
                    allBlockVertices.push_back(*vertex);
                }
            }
        }
    }

    MC_PROFILE_END(Profiler::TimeFrame::SECONDS);

    uint32_t countBlockFaces = allBlockVertices.size() / Mc::BlockFace::s_countBlockFaceVertices;

    std::vector<uint32_t> blockFaceIndices;
    uint32_t maxIndex = 0;
    for (int i = 0; i < countBlockFaces; i++)
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
    FpsCounter fpsCounter;

    fpsCounter.Init();

    while (m_windowHandle->IsOpen())
    {
        ts.stop();
        ts.start();

        if (Window::IsKeyPressed(KEY_W))
            m_player->MoveForward(ts);
        if (Window::IsKeyPressed(KEY_S))
            m_player->MoveBackward(ts);
        if (Window::IsKeyPressed(KEY_A))
            m_player->StrafeLeft(ts);
        if (Window::IsKeyPressed(KEY_D))
            m_player->StrafeRight(ts);
        if (Window::IsKeyPressed(KEY_SPACE))
            m_player->MoveUp(ts);

        if (!m_player->IsSprinting() && Window::IsKeyPressed(KEY_LEFT_SHIFT))
        {
            m_player->SetSprinting(true);
            m_player->SetSpeed(m_player->GetSpeed() * 2.0f);
        }
        else if(m_player->IsSprinting() && !Window::IsKeyPressed(KEY_LEFT_SHIFT))
        {
            m_player->SetSprinting(false);
            m_player->SetSpeed(m_player->GetSpeed() / 2.0f);
        }

        Renderer::OnUpdate();
        fpsCounter.Update();
        std::cout << "FPS: " << fpsCounter.GetFPS() << std::endl;
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