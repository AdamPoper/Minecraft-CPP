#pragma once

#include "../Renderer/Renderer.h"
#include "../world/World.h"
#include "../Util/FpsCounter.h"
#include "../Player/Player.h"

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

	float m_playerSpeed = 10.0f;

	Ref<Window> m_windowHandle;

	Ref<Player> m_player;
};