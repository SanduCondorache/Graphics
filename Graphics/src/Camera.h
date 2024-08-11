#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float FOV = 45.0f;
const float NEAR = 0.1f;
const float FAR = 500.0f;
const float MAXPITCH = 89.0f;
const float MAXFOV = 45.0f;
const float MINFOV = 1.0f;
const float CAMERASPEED = 5.0f;

class Camera {
public:
	Camera(float Width, float Height);

	void SetScreenSize(float width, float height);
	void SetFov(float fov);
	
	inline glm::vec3 getCameraPos() const { return m_Position; }
	inline glm::vec3 getCameraFront() const { return m_Front; }
	inline glm::vec3 getCameraRight() const { return m_Right; }
	inline glm::vec3 getCameraUp() const { return m_Up; }
	 
	inline float getYaw() const { return m_Yaw; }
	inline float getPitch() const { return m_Pitch; }
	inline float getCameraSpeed() const { return m_CameraSpeed; }
	
	inline glm::vec2 getScreenSize() const { return glm::vec2(m_Width, m_Height); }
	inline float getFov() const { return m_Fov; }

	glm::mat4 ViewMatrix() const;
	glm::mat4 PerspectiveMatrix() const;

	void CameraRotate(float deltaYaw, float deltaPitch);
	void CameraMove(float CameraFront, float CameraUp, float CameraRight);
	void CameraSetPos(glm::vec3 _pos);
	void MoveUp(float amount);

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
