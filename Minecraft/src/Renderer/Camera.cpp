#include "Camera.h"

Camera::Camera(float w, float h)
	: m_view(1.0f), m_cameraPosition(0.0f, 0.0f, 4.0f), m_cameraTarget(0.0f, 0.0f, 0.0f),
	m_cameraFront(0.0f, 0.0f, -1.0f), m_cameraUp(0.0f, 1.0f, 0.0f), m_windowWidth(w), m_windowHeight(h)
{
	m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
	m_projection = glm::perspective(glm::radians(m_fov), m_windowWidth / m_windowHeight, 0.1f, 100.0f);
}

Camera::Camera(const Camera& cam)
{

}

void Camera::translate(const glm::vec3& vec)
{
	m_view = glm::translate(m_view, vec);
}

void Camera::onUpdate()
{
	m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
	m_projection = glm::perspective(glm::radians(m_fov), m_windowWidth / m_windowHeight, 0.1f, 100.0f);
}

void Camera::moveForward(TimeStep ts)
{
	m_cameraPosition += m_cameraSpeed * ts * m_cameraFront;
}

void Camera::moveBackward(TimeStep ts)
{
	m_cameraPosition -= m_cameraSpeed * ts * m_cameraFront;
}

void Camera::strafeLeft(TimeStep ts)
{
	m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed * (float)ts;
}

void Camera::strafeRight(TimeStep ts)
{
	m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed * (float)ts;
}

void Camera::adjustFov(float offset)
{
	m_fov -= offset;
}

void Camera::SetCameraSpeed(float speed)
{
	m_cameraSpeed = speed;
}

float Camera::GetCameraSpeed()
{
	return m_cameraSpeed;
}

void Camera::TranslatePosition(const glm::vec3& transform)
{
	m_cameraPosition += transform;
}

glm::vec3 Camera::GetPosition()
{
	return m_cameraPosition;
}

void Camera::onCameraMouseMove(double xpos, double ypos)
{
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_cameraFront = glm::normalize(direction);
}