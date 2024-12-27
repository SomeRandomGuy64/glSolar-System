#include "Camera.h"

void Camera::processKeyboard(CameraMovement direction, float dt) {
	float velocity = m_movementSpeed * dt;
	
	switch (direction) {
	case FORWARD:	m_position += m_front * velocity;	break;
	case BACKWARD:	m_position -= m_front * velocity;	break;
	case LEFT:		m_position -= m_right * velocity;	break;
	case RIGHT:		m_position += m_right * velocity;	break;
	case UP:		m_position += m_up    * velocity;	break;
	case DOWN:		m_position -= m_up    * velocity;	break;
	default:		m_position;							break;
	}

}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= m_mouseSensitivity;
	yOffset *= m_mouseSensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	// pitch can't go above 89 degrees, this prevents the camera from flipping
	if (constrainPitch) {
		if (m_pitch > 89.0f) {
			m_pitch = 89.0f;
		}
		else if (m_pitch < -89.0f) {
			m_pitch = -89.0f;
		}
	}

	m_updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {

	m_fov -= static_cast<float>(yOffset);
	if (m_fov < 1.0f) {
		m_fov = 1.0f;
	}
	else if (m_fov > 120.0f) {
		m_fov = 120.0f;
	}

}

void Camera::m_updateCameraVectors() {

	glm::vec3 front{
		glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)),
		glm::sin(glm::radians(m_pitch)),
		glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch))
	};
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
