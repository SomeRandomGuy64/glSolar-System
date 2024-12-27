#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {

public:
	Shader() {};

	unsigned int getID() { return m_ID; }

	Shader& use();
	void compile(const char* vertexSource, const char* fragmantSource);

	void setFloat(const char* name, float value, bool useShader = false);
	void setInteger(const char* name, int value, bool useShader = false);
	void setVec2f(const char* name, float x, float y, bool useShader = false);
	void setVec2f(const char* name, const glm::vec2& value, bool useShader = false);
	void setVec3f(const char* name, float x, float y, float z, bool useShader = false);
	void setVec3f(const char* name, const glm::vec3& value, bool useShader = false);
	void setVec4f(const char* name, float x, float y, float z, float w, bool useShader = false);
	void setVec4f(const char* name, const glm::vec4& value, bool useShader = false);
	void setMat2(const char* name, const glm::mat2& matrix, bool useShader = false);
	void setMat3(const char* name, const glm::mat3& matrix, bool useShader = false);
	void setMat4(const char* name, const glm::mat4& matrix, bool useShader = false);

private:

	unsigned int m_ID{};

	void m_checkCompileErrors(unsigned int object, std::string type);

};