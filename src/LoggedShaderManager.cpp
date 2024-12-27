#include "LoggedShaderManager.h"

#include <fmt/core.h>
#include <fmt/color.h>

#include <sstream>
#include <fstream>

Shader LoggedShaderManager::loadShader(const char* vShaderFile, const char* fShaderFile, std::string name) {
	fmt::print(
		fmt::emphasis::bold | fg(fmt::color::blue),
		"Shader: loadShader()\n"
	);
	return m_wrapped.loadShader(vShaderFile, fShaderFile, name);
}

Shader& LoggedShaderManager::getShader(std::string name) {
	fmt::print(
		fmt::emphasis::bold | fg(fmt::color::blue),
		"Shader: getShader()\n"
	);
	return m_wrapped.getShader(name);
}

void LoggedShaderManager::clear() {
	fmt::print(
		fmt::emphasis::bold | fg(fmt::color::red),
		"Shader: clear()\n"
	);
	m_wrapped.clear();
}