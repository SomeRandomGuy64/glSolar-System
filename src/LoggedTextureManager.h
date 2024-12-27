#pragma once

#include "TextureManager.h"

class LoggedTextureManager : public ITextureManager {

public:
	LoggedTextureManager(TextureManager wrapped) : m_wrapped(wrapped) {};

	virtual Texture& loadTexture(const char* file, bool alpha, std::string name);
	virtual Texture& getTexture(std::string name);
	virtual void clear();

private:

	TextureManager m_wrapped;

	virtual Texture m_loadTextureFromFile(const char*, bool) { return Texture(); }

};
