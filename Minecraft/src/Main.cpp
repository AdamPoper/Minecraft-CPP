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
#include "world/World.h"
#include "Renderer/Renderer.h"
#include "Game/Game.h"

int main()
{
	Game::OnInit();
	Game::OnGameRun();

  // Renderer::SetTextureAtlasFilePath("res/textures/atlas.png", 3, 3);
  // Renderer::SetWindowViewDimensions(1920.0f, 1080.0f);
  // Renderer::OnInit();
  //
  // Mc::World::OnInit();
  //
  // const std::vector<Mc::Block>& blocks = Mc::World::GetBlocks();
  //
  // std::vector<Vertex> allBlockVertices;
  // for (const Mc::Block& block : blocks)
  // {
  //     for (const Vertex* vertex : block.GetVertices())
  //     {
  //         allBlockVertices.push_back(*vertex);
  //     }
  // }
  //
  // std::vector<uint32_t> blockFaceIndices;
  // uint32_t maxIndex = 0;
  // for (int i = 0; i < blocks.size() * Mc::Block::s_blockFacesCount; i++)
  // {
  //     uint32_t index0 = maxIndex; maxIndex++;
  //     uint32_t index1 = maxIndex; maxIndex++;
  //     uint32_t index2 = maxIndex; maxIndex++;
  //     uint32_t index3 = maxIndex; maxIndex++;
  //
  //     blockFaceIndices.push_back(index0);
  //     blockFaceIndices.push_back(index1);
  //     blockFaceIndices.push_back(index2);
  //     blockFaceIndices.push_back(index0);
  //     blockFaceIndices.push_back(index2);
  //     blockFaceIndices.push_back(index3);
  // }
  //
  // Renderer::SetVertexData(allBlockVertices.data(), allBlockVertices.size());
  // Renderer::SetIndexData(blockFaceIndices.data(), blockFaceIndices.size());
  //
  // float speed = 5.0f;
  //
  // TimeStep ts;
  //
  // Window& window = *Renderer::GetWindow();
  //
  // while (window.IsOpen())
  // {
  //     ts.stop();
  //     ts.start();
  //
  //     if (Window::IsKeyPressed(KEY_W))
  //         window.GetCamera().moveForward(ts);
  //     if (Window::IsKeyPressed(KEY_S))
  //         window.GetCamera().moveBackward(ts);
  //     if (Window::IsKeyPressed(KEY_A))
  //         window.GetCamera().strafeLeft(ts);
  //     if (Window::IsKeyPressed(KEY_D))
  //         window.GetCamera().strafeRight(ts);
  //
  //     Renderer::OnUpdate();
  // }
}