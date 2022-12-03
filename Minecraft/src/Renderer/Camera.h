#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

#include "../Util/TimeStep.h"

class Camera
{
public:
	Camera(float w, float h);

	Camera(const Camera&);

	void translate(const glm::vec3& vec);

	const glm::mat4& getView() const { return m_view; }

	void onCameraMouseMove(double xpos, double ypos);

	void onUpdate();

	void moveForward(TimeStep ts);

	void moveBackward(TimeStep ts);

	void strafeLeft(TimeStep ts);

	void strafeRight(TimeStep ts);

	void adjustFov(float offset);

	void SetCameraSpeed(float speed);

	float getFov() { return m_fov; }

	const glm::mat4& const getProjection() { return m_projection; }

private:
	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraTarget;
	glm::vec3 m_cameraUp;
	glm::mat4 m_cameraDirection;
	glm::mat4 m_view;
	glm::vec3 m_cameraFront;

	glm::mat4 m_projection;

private:

	float m_fov = 90.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool firstMouse = true;
	float lastX = 800.0f / 2.0f;
	float lastY = 600.0f / 2.0f;
	float m_cameraSpeed = 3.5f;

	float m_windowWidth, m_windowHeight;
};