#pragma once

#include "../Renderer/Renderer.h"
#include "../world/World.h"

class Game
{
public:

	static void OnInit();

	static void OnGameRun();

private:

	Game() = default;

	Game(const Game&) = delete;

	void OnGameInit();

	void Run();

	static Game s_gameInstance;

private:

	float m_playerSpeed = 5.0f;

	Ref<Window> m_windowHandle;

};