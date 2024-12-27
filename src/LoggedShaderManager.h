#pragma once

#include "ShaderManager.h"

class LoggedShaderManager : public IShaderManager {

public:
	LoggedShaderManager(ShaderManager wrapped) : m_wrapped(wrapped) {};

	virtual Shader loadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
	virtual Shader& getShader(std::string name);
	virtual void clear();

private:

	ShaderManager m_wrapped;

	virtual Shader m_loadShaderFromFile(const char*, const char*) { return Shader(); }

};
