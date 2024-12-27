#pragma once

#include "Shader.h"
#include "Camera.h"
#include <glm/glm.hpp>

class Sphere {

public:
	Sphere(Camera& camera, Shader& shader);
	~Sphere() = default;

	void draw(glm::vec3 position, float radius);

private:
	Camera& m_camera;

	Shader m_shader{};
	unsigned int m_vao{ 0 };
	unsigned int m_indexCount{};
	
	const unsigned int m_segments{ 32 };

	void m_initData();
};
