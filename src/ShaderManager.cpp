#include "ShaderManager.h"

#include <fmt/core.h>
#include <fmt/color.h>

#include <sstream>
#include <fstream>

Shader ShaderManager::loadShader(const char* vShaderFile, const char* fShaderFile, std::string name) {
	m_shaders[name] = m_loadShaderFromFile(vShaderFile, fShaderFile);
	return m_shaders[name];
}

void ShaderManager::clear() {
	for (auto shader : m_shaders) {
		glDeleteProgram(shader.second.getID());
	}
}

Shader ShaderManager::m_loadShaderFromFile(const char* vShaderFile, const char* fShaderFile) {
	std::string vertexCode{};
	std::string fragmentCode{};

	try {
		std::ifstream vertexShaderFile{ vShaderFile };
		std::stringstream vShaderStream{};
		vShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();
		vertexCode = vShaderStream.str();

		std::ifstream fragmentShaderFile{ fShaderFile };
		std::stringstream fShaderStream{};
		fShaderStream << fragmentShaderFile.rdbuf();
		fragmentShaderFile.close();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception error) {
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
			"Error: Failed to read shader files\n");
	}

	const char* vShaderCode{ vertexCode.c_str() };
	const char* fShaderCode{ fragmentCode.c_str() };

	Shader shader{};
	shader.compile(vShaderCode, fShaderCode);
	return shader;

}