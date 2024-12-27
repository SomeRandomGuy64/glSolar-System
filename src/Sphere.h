#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <glm/glm.hpp>

class Sphere {

public:
	Sphere(Camera& camera, Shader& shader, Texture& texture);
	~Sphere() = default;

	void draw(glm::vec3 position, float radius);

private:
	Camera& m_camera;

	Shader m_shader{};
	Texture m_texture{};

	unsigned int m_vao{ 0 };
	unsigned int m_indexCount{};
	
	const unsigned int m_segments{ 64 };

	void m_initData();
};
