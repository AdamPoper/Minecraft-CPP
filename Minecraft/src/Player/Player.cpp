#include "Player.h"

Player::Player()
{

}

void Player::SetCamera(Ref<Camera> camera)
{
	m_camera = camera;
}

Ref<Camera> Player::GetCamera()
{
	return m_camera;
}

void Player::StrafeRight(TimeStep ts)
{
	m_camera->strafeRight(ts);
}

void Player::StrafeLeft(TimeStep ts)
{
	m_camera->strafeLeft(ts);
}

void Player::MoveForward(TimeStep ts)
{
	m_camera->moveForward(ts);
}

void Player::MoveBackward(TimeStep ts)
{
	m_camera->moveBackward(ts);
}

glm::vec3 Player::GetPostion()
{
	return m_camera->GetPosition();
}

void Player::TranslatePlayer(glm::vec3 transform)
{
	m_camera->TranslatePosition(transform);
}

void Player::SetSpeed(float speed)
{
	m_camera->SetCameraSpeed(speed);
}

float Player::GetSpeed()
{
	return m_camera->GetCameraSpeed();
}

bool Player::IsSprinting()
{
	return m_isSprinting;
}

void Player::SetSprinting(bool isSprinting)
{
	m_isSprinting = isSprinting;
}