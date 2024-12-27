#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
namespace cameraValues {
	constexpr float yaw{ -90.0f };
	constexpr float pitch{ 0.0f };
	constexpr float speed{ 0.01f };
	constexpr float sensitivity{ 0.1f };
	constexpr float FOV{ 60.0f };
}

// camera class which calculates euler angles from any input processed
// improve this later to support quaternions
class Camera {

public:

	// constructor using glm vectors
	Camera(
		glm::vec3 position = glm::vec3{ 0.0f },
		glm::vec3 worldUp = glm::vec3{ 0.0f, 1.0f, 0.0f },
		float yaw = cameraValues::yaw,
		float pitch = cameraValues::pitch)
		: m_front{ glm::vec3{ 0.0f, 0.0f, -1.0f } }
		, m_movementSpeed{ cameraValues::speed }
		, m_mouseSensitivity{ cameraValues::sensitivity }
		, m_fov{ cameraValues::FOV }
	{
		m_position = position;
		m_worldUp = worldUp;
		m_yaw = yaw;
		m_pitch = pitch;
		m_updateCameraVectors();
	}

	// constructor using scalar values
	Camera(
		float posX,
		float posY = 0.0f,
		float posZ = 0.0f,
		float upX = 0.0f,
		float upY = 1.0f,
		float upZ = 0.0f,
		float yaw = cameraValues::yaw,
		float pitch = cameraValues::pitch)
		: m_front{ glm::vec3{ 0.0f, 0.0f, -1.0f } }
		, m_movementSpeed{ cameraValues::speed }
		, m_mouseSensitivity{ cameraValues::sensitivity }
		, m_fov{ cameraValues::FOV }
	{
		m_position = glm::vec3{ posX, posY, posZ };
		m_worldUp = glm::vec3{ upX, upY, upZ };
		m_yaw = yaw;
		m_pitch = pitch;
		m_updateCameraVectors();
	}

	float getFOV() { return m_fov; }
	glm::vec3 getPosition() { return m_position; }
	glm::vec3 getFront() { return m_front; }
	glm::mat4 getViewMatrix() { return glm::lookAt(m_position, m_position + m_front, m_up); }

	void processKeyboard(CameraMovement direction, float dt);
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void processMouseScroll(float yOffset);

private:

	// camera attributes
	glm::vec3 m_position{};
	glm::vec3 m_front{ 0.0f, 0.0f, -1.0f };
	glm::vec3 m_up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 m_right{};
	glm::vec3 m_worldUp{};

	// euler angles
	float m_yaw{ cameraValues::yaw };
	float m_pitch{ cameraValues::pitch };

	// camera options
	float m_movementSpeed{ cameraValues::speed };
	float m_mouseSensitivity{ cameraValues::sensitivity };
	float m_fov{ cameraValues::FOV };

	void m_updateCameraVectors();

};
