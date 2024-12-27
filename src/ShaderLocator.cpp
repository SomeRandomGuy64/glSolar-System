#include "ShaderLocator.h"

#if NDEBUG
ShaderManager ShaderLocator::m_service;
#else
LoggedShaderManager ShaderLocator::m_service{ ShaderManager() };
#endif
