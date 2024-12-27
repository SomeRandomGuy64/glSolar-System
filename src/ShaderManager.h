#pragma once

#include "IShaderManager.h"

class ShaderManager : public IShaderManager {

public:
	ShaderManager() {};

	virtual Shader loadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
	virtual void clear();

	virtual Shader& getShader(std::string name) { return m_shaders[name]; }

private:

	std::map<std::string, Shader> m_shaders{};
	virtual Shader m_loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);

};
