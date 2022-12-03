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

private:

	static Game s_gameInstance;

private:

	float m_playerSpeed = 5.0f;

	bool m_isPlayerSprinting = false;

	Ref<Window> m_windowHandle;
};