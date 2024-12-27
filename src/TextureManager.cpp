#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

Texture& TextureManager::loadTexture(const char* file, bool alpha, std::string name) {
	m_textures[name] = m_loadTextureFromFile(file, alpha);
	return m_textures[name];
}

void TextureManager::clear() {
	for (auto texture : m_textures) {
		glDeleteTextures(1, &texture.second.getIdRef());
	}
}

Texture TextureManager::m_loadTextureFromFile(const char* file, bool alpha) {

	Texture texture{};
	if (alpha) {
		texture.setInternalFormat(GL_RGBA);
		texture.setImageFormat(GL_RGBA);
	}

	int width{};
	int height{};
	int nrChannels{};
	unsigned char* data{ stbi_load(file, &width, &height, &nrChannels, 0) };

	texture.generate(width, height, data);

	stbi_image_free(data);
	return texture;

}
