#include "Camera.h"

Camera::Camera(float _screenWidth, float _screenHeight, float _cameraSpeed ,float _fov, float _pitch, float _yaw, glm::vec3 _m_Position, glm::vec3 _worldUp, float _nearPlane, float _farPlane)
	: m_Fov(_fov), m_Pitch(_pitch), m_Yaw(_yaw), m_Position(_m_Position), m_WorldUp(_worldUp), m_Height(_screenHeight), m_Width(_screenWidth),
	  m_Near(_nearPlane), m_Far(_farPlane), m_CameraSpeed(_cameraSpeed)
{
	updateVectors();
}


glm::mat4 Camera::viewMatrix() {
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::perspectiveMatrix() {
	return glm::perspective(glm::radians(m_Fov), m_Width / m_Height, m_Near, m_Far);
}


void Camera::setScreenSize(float _width, float _height) {
	m_Width = _width;
	m_Height = _height;
}


void Camera::setFOV(float _fov) {
	m_Fov = _fov;
}


void Camera::cameraSetFOV(float _fov) {
	m_Fov = _fov;
}

void Camera::cameraRotate(float _delta_yaw, float _delta_pitch, bool constrainPitch, float constrainVal) {
	m_Pitch += _delta_pitch;
	m_Yaw += _delta_yaw;

	if (constrainPitch) {
		constrainVal = abs(constrainVal);
		if (m_Pitch > constrainVal)
			m_Pitch = constrainVal;
		if (m_Pitch < -constrainVal)
			m_Pitch = -constrainVal;
	}

	updateVectors();
}

void Camera::cameraMove(float CameraFront, float CameraUp, float CameraRight) {
	m_Position += CameraFront * m_Front + CameraUp * m_Up + CameraRight * m_Right;
}

void Camera::cameraSetPos(glm::vec3 _pos) {
	m_Position = _pos;
}

void Camera::moveUp(float amount) {
	m_Position.y += amount;
}


// Private

void Camera::updateVectors() {
	// calculate the new Front vector
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);
	// also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}