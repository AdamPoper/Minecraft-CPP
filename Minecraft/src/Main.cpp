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
}