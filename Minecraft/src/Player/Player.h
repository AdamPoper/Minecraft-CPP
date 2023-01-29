#pragma once

#include "../Renderer/Camera.h"
#include "../glm/glm.hpp"
#include "../Util/Ref.h"

class Player
{
public:

	Player();

	Player(const Player&) = delete;

	void SetCamera(Ref<Camera> camera);

	Ref<Camera> GetCamera();

	void StrafeRight(TimeStep ts);

	void StrafeLeft(TimeStep ts);

	void MoveForward(TimeStep ts);

	void MoveBackward(TimeStep ts);

	glm::vec3 GetPostion();

	void TranslatePlayer(glm::vec3 transform);

	void SetSpeed(float speed);

	float GetSpeed();

	bool IsSprinting();

	void SetSprinting(bool isSprinting);

private:

	Ref<Camera> m_camera;

	float m_speed;

	bool m_isSprinting;
};