#pragma once

#include "ShaderManager.h"
#include "LoggedShaderManager.h"

class ShaderLocator {

public:
	static IShaderManager& getShaderManager() { return m_service; }

private:
#if NDEBUG
	static ShaderManager m_service;
#else
	static LoggedShaderManager m_service;
#endif

};
