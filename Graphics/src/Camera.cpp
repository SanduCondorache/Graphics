#include "Camera.h"

Camera::Camera(float Width, float Height)
	: m_Fov(FOV), m_Pitch(PITCH), m_Yaw(YAW), m_Position(glm::vec3(0.0f, 0.0f, 3.0f)), m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), 
	  m_Height(Height), m_Width(Width), m_Near(NEAR), m_Far(FAR), m_CameraSpeed(CAMERASPEED)
{
	updateVectors();
}


glm::mat4 Camera::ViewMatrix() const {
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::PerspectiveMatrix() const {
	return glm::perspective(glm::radians(m_Fov), m_Width / m_Height, m_Near, m_Far);
}


void Camera::SetScreenSize(float width, float height) {
	m_Width = width;
	m_Height = height;
}


void Camera::SetFov(float fov) {
	m_Fov = fov;
	if (m_Fov < MINFOV) {
		m_Fov = MINFOV;
	}
	else if (m_Fov > MAXFOV) {
		m_Fov = MAXFOV;
	}
}

void Camera::CameraRotate(float deltaYaw, float deltaPitch) {
	m_Pitch += deltaPitch;
	m_Yaw += deltaYaw;
	if (m_Pitch > MAXPITCH)
		m_Pitch = MAXPITCH;
	if (m_Pitch < -MAXPITCH)
		m_Pitch = -MAXPITCH;
	updateVectors();
}

void Camera::CameraMove(float CameraFront, float CameraUp, float CameraRight) {
	m_Position += CameraFront * m_Front + CameraUp * m_Up + CameraRight * m_Right;
}

void Camera::CameraSetPos(glm::vec3 pos) {
	m_Position = pos;
}

void Camera::MoveUp(float amount) {
	m_Position.y += amount;
}

void Camera::updateVectors() {
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}