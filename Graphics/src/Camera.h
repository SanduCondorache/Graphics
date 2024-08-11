#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float FOV = 45.0f;
const float NEAR = 0.1f;
const float FAR = 500.0f;

class Camera {
public:
	Camera(float screenWidth, float screenHeight, float cameraSpeed,
		float fov = FOV, float pitch = PITCH, float yaw = YAW,
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
		float nearPlane = NEAR, float farPlane = FAR);

	void setScreenSize(float _width, float _height);
	void setFOV(float _fov);
	
	inline glm::vec3 getCameraPos() const { return m_Position; }
	inline glm::vec3 getCameraFront() const { return m_Front; }
	inline glm::vec3 getCameraRight() const { return m_Right; }
	inline glm::vec3 getCameraUp() const { return m_Up; }
	 
	inline float getYaw() const { return m_Yaw; }
	inline float getPitch() const { return m_Pitch; }
	inline float getCameraSpeed() const { return m_CameraSpeed; }
	
	inline glm::vec2 getScreenSize() const { return glm::vec2(m_Width, m_Height); }
	inline float getFOV() const { return m_Fov; }

	glm::mat4 viewMatrix();
	glm::mat4 perspectiveMatrix();


	// camera movement
	void cameraSetFOV(float _fov);
	void cameraRotate(float _delta_yaw, float _delta_pitch, bool constrainPitch = true, float constrainVal = 89.0f);
	void cameraMove(float CameraFront, float CameraUp, float CameraRight);
	void cameraSetPos(glm::vec3 _pos);
	void moveUp(float amount);

private:
	// camera atributes
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// perspective
	float m_Fov;
	float m_Width, m_Height;
	float m_Near, m_Far;
	float m_CameraSpeed;

	// euler Angles
	float m_Yaw;
	float m_Pitch;

	void updateVectors();
};
