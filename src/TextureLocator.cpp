#include "TextureLocator.h"

#if NDEBUG
TextureManager TextureLocator::m_service;
#else
LoggedTextureManager TextureLocator::m_service{ TextureManager() };
#endif
