#pragma once

#include "TextureManager.h"
#include "LoggedTextureManager.h"

class TextureLocator {

public:
	static ITextureManager& getTextureManager() { return m_service; }

private:
#if NDEBUG
	static TextureManager m_service;
#else
	static LoggedTextureManager m_service;
#endif

};
