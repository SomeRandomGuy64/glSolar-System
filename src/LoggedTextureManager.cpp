#include "LoggedTextureManager.h"

#include <fmt/core.h>
#include <fmt/color.h>

#include <sstream>
#include <fstream>

Texture& LoggedTextureManager::loadTexture(const char* file, bool alpha, std::string name) {
	fmt::print(
		fmt::emphasis::bold | fg(fmt::color::blue),
		"Texture: loadTexture()\n"
	);
	return m_wrapped.loadTexture(file, alpha, name);
}

Texture& LoggedTextureManager::getTexture(std::string name) {
	fmt::print(
		fmt::emphasis::bold | fg(fmt::color::blue),
		"Texture: getTexture()\n"
	);
	return m_wrapped.getTexture(name);
}

void LoggedTextureManager::clear() {
	fmt::print(
		fmt::emphasis::bold | fg(fmt::color::red),
		"Texture: clear()\n"
	);
	m_wrapped.clear();
}