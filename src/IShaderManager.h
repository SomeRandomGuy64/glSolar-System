#pragma once

#include <string>
#include <map>

#include <glad/glad.h>

#include "shader.h"

class IShaderManager {

public:
	virtual Shader loadShader(const char* vShaderFile, const char* fShaderFile, std::string name) = 0;
	virtual Shader& getShader(std::string name) = 0;
	virtual void clear() = 0;

protected:
	virtual Shader m_loadShaderFromFile(const char* vShaderFile, const char* fShaderFile) = 0;

};
