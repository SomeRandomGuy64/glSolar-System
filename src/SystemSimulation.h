#pragma once

#include "Camera.h"

#include <SDL3/SDL.h>

enum class SimulationState {
	ACTIVE,
	MENU
};

class Simulation {

public:
	Simulation(unsigned int width, unsigned int height) : m_width(width), m_height(height) {};
	~Simulation() = default;

	void init();
	void processKey(float dt);
	void processMouse(float xOffset, float yOffset);
	void update(float dt);
	void render();

private:
	SimulationState m_state{ SimulationState::ACTIVE };
	const Uint8* m_keys{ SDL_GetKeyboardState(nullptr) };
	unsigned int m_width{};
	unsigned int m_height{};

	Camera m_camera{};

};
