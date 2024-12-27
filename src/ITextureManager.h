#pragma once

#include <string>
#include <map>

#include <glad/glad.h>

#include "Texture.h"

class ITextureManager {

public:
	virtual Texture& loadTexture(const char* file, bool alpha, std::string name) = 0;
	virtual Texture& getTexture(std::string name) = 0;
	virtual void clear() = 0;

protected:
	virtual Texture m_loadTextureFromFile(const char* file, bool alpha) = 0;

};
