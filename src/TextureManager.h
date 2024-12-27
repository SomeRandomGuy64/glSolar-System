#pragma once

#include "ITextureManager.h"

class TextureManager : public ITextureManager {

public:
	TextureManager() {};

	virtual Texture& loadTexture(const char* file, bool alpha, std::string name);
	virtual void clear();

	virtual Texture& getTexture(std::string name) { return m_textures[name]; }

private:

	std::map<std::string, Texture> m_textures{};
	virtual Texture m_loadTextureFromFile(const char* file, bool alpha);

};
