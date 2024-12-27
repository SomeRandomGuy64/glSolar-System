#include "Sphere.h"
#include "ShaderLocator.h"
#include "TextureLocator.h"

#include <glad/glad.h>
#include <glm/gtc/constants.hpp>

#include <vector>

Sphere::Sphere(Camera& camera, Shader& shader, Texture& texture)
	: m_camera(camera)
	, m_shader(shader)
	, m_texture(texture)
{
	m_initData();
}

void Sphere::draw(glm::vec3 position, float radius) {
	m_shader.use();

	ShaderLocator::getShaderManager().getShader("sphere").use().setMat4("view", m_camera.getViewMatrix());
	ShaderLocator::getShaderManager().getShader("sphere").use().setInt("material.diffuse", 0);
	ShaderLocator::getShaderManager().getShader("sphere").use().setInt("material.specular", 0);
	ShaderLocator::getShaderManager().getShader("sphere").use().setInt("material.emission", 0);
	ShaderLocator::getShaderManager().getShader("sphere").use().setFloat("material.shininess", 256.0f);
	ShaderLocator::getShaderManager().getShader("sphere").use().setVec3f("pointLight.position", glm::vec3{ 0.0f, 0.0f, -5.0f });
	ShaderLocator::getShaderManager().getShader("sphere").use().setFloat("pointLight.constant", 1.0f);
	ShaderLocator::getShaderManager().getShader("sphere").use().setFloat("pointLight.linear", 0.001f);
	ShaderLocator::getShaderManager().getShader("sphere").use().setFloat("pointLight.quadratic", 0.000001f);
	ShaderLocator::getShaderManager().getShader("sphere").use().setVec3f("pointLight.ambient", glm::vec3{ 0.1f, 0.1f, 0.1f });
	ShaderLocator::getShaderManager().getShader("sphere").use().setVec3f("pointLight.diffuse", glm::vec3{ 0.8f, 0.8f, 0.8f });
	ShaderLocator::getShaderManager().getShader("sphere").use().setVec3f("pointLight.specular", glm::vec3{ 1.0f, 0.0f, 0.0f });

	glm::mat4 modelMatrix{ 1.0f };
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3{ radius });
	ShaderLocator::getShaderManager().getShader("sphere").use().setMat4("model", modelMatrix);

	glActiveTexture(GL_TEXTURE0);
	TextureLocator::getTextureManager().getTexture("sun").bind();

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLE_STRIP, m_indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void Sphere::m_initData() {

	if (m_vao == 0) {
		glGenVertexArrays(1, &m_vao);

		std::vector<glm::vec3> positions{};
		std::vector<glm::vec3> normals{};
		std::vector<glm::vec2> uv{};
		std::vector<unsigned int> indicies{};

		const unsigned int X_SEGMENTS{ m_segments };
		const unsigned int Y_SEGMENTS{ m_segments };

		for (unsigned int x{ 0 }; x <= X_SEGMENTS; ++x) {
			for (unsigned int y{ 0 }; y <= Y_SEGMENTS; ++y) {
				float xSegment{ (float)x / (float)X_SEGMENTS };
				float ySegment{ (float)y / (float)Y_SEGMENTS };

				float xPos{ glm::cos(xSegment * 2.0f * glm::pi<float>()) * glm::sin(ySegment * glm::pi<float>()) };
				float yPos{ glm::cos(ySegment * glm::pi<float>()) };
				float zPos{ glm::sin(xSegment * 2.0f * glm::pi<float>()) * glm::sin(ySegment * glm::pi<float>()) };

				positions.push_back(glm::vec3{ xPos, yPos, zPos });
				normals.push_back(glm::vec3{ xPos, yPos, zPos });
				uv.push_back(glm::vec2{ xSegment, ySegment });
			}
		}

		bool oddRow{ false };
		for (unsigned int y{ 0 }; y < Y_SEGMENTS; ++y) {
			if (!oddRow) {
				for (unsigned int x{ 0 }; x <= X_SEGMENTS; ++x) {
					indicies.push_back(y * (X_SEGMENTS + 1) + x);
					indicies.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				}
			}
			else {
				for (int x{ (int)X_SEGMENTS }; x >= 0; --x) {
					indicies.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					indicies.push_back(y * (X_SEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}

		m_indexCount = static_cast<unsigned int>(indicies.size());

		std::vector<float> data{};
		for (unsigned int i{ 0 }; i < positions.size(); ++i) {
			data.push_back(positions.at(i).x);
			data.push_back(positions.at(i).y);
			data.push_back(positions.at(i).z);
			if (normals.size() > 0) {
				data.push_back(normals.at(i).x);
				data.push_back(normals.at(i).y);
				data.push_back(normals.at(i).z);
			}
			if (uv.size() > 0) {
				data.push_back(uv.at(i).x);
				data.push_back(uv.at(i).y);
			}
		}

		unsigned int vbo{};
		glGenBuffers(1, &vbo);
		unsigned int ebo{};
		glGenBuffers(1, &ebo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

		unsigned int positionsVectorSize{ 3 };
		unsigned int normalsVectorSize{ 3 };
		unsigned int uvVectorSize{ 2 };
		unsigned int stride{ (positionsVectorSize + normalsVectorSize + uvVectorSize) * sizeof(float) };

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

		glBindVertexArray(0);
	}
}
