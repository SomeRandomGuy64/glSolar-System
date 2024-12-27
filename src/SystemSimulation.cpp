#include "SystemSimulation.h"
#include "Sphere.h"
#include "ShaderLocator.h"
#include "TextureLocator.h"

Sphere *sun;

void Simulation::init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);

	glPolygonMode(GL_FRONT, GL_FILL);

	ShaderLocator::getShaderManager().loadShader("../shaders/lighting.vert", "../shaders/lighting.frag", "sphere");
	TextureLocator::getTextureManager().loadTexture("../textures/2k_sun.jpg", false, "sun");

	glm::mat4 projection{
		glm::perspective(
			glm::radians(m_camera.getFOV()),
			(float)m_width / (float)m_height,
			0.1f,
			100.0f
		)
	};

	ShaderLocator::getShaderManager().getShader("sphere").use().setMat4("projection", projection);

	sun = new Sphere(
		m_camera, 
		ShaderLocator::getShaderManager().getShader("sphere"),
		TextureLocator::getTextureManager().getTexture("sun")
	);

}

void Simulation::processKey(float dt) {

	if (m_state == SimulationState::ACTIVE) {

		if (m_keys[SDL_SCANCODE_W]) {
			m_camera.processKeyboard(FORWARD, dt);
		}
		if (m_keys[SDL_SCANCODE_S]) {
			m_camera.processKeyboard(BACKWARD, dt);
		}
		if (m_keys[SDL_SCANCODE_A]) {
			m_camera.processKeyboard(LEFT, dt);
		}
		if (m_keys[SDL_SCANCODE_D]) {
			m_camera.processKeyboard(RIGHT, dt);
		}
		if (m_keys[SDL_SCANCODE_SPACE]) {
			m_camera.processKeyboard(UP, dt);
		}
		if (m_keys[SDL_SCANCODE_LCTRL]) {
			m_camera.processKeyboard(DOWN, dt);
		}

	}

}

void Simulation::processMouse(float xOffset, float yOffset) {
	m_camera.processMouseMovement(xOffset, yOffset);
}

void Simulation::update(float) {}

void Simulation::render() {

	sun->draw(glm::vec3{ 0.0f, 0.0f, -5.0f }, 1.0f);

}