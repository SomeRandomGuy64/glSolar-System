#include "shader.h"

#include <fmt/core.h>
#include <fmt/color.h>

Shader& Shader::use() {

	glUseProgram(m_ID);
	return *this;

}

void Shader::compile(const char* vertexSource, const char* fragmentSource) {
	fmt::print("{}\n", fragmentSource);

	unsigned int sVertex{};
	unsigned int sFragment{};

	// vertex shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, nullptr);
	glCompileShader(sVertex);
	m_checkCompileErrors(sVertex, "VERTEX");

	// fragment shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, nullptr);
	glCompileShader(sFragment);
	m_checkCompileErrors(sFragment, "FRAGMENT");

	m_ID = glCreateProgram();
	glAttachShader(m_ID, sVertex);
	glAttachShader(m_ID, sFragment);
	glLinkProgram(m_ID);
	m_checkCompileErrors(m_ID, "PROGRAM");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);

}

void Shader::setFloat(const char* name, float value, bool useShader) {
	if (useShader) use();
	glUniform1f(glGetUniformLocation(m_ID, name), value);
}

void Shader::setInt(const char* name, int value, bool useShader) {
	if (useShader) use();
	glUniform1i(glGetUniformLocation(m_ID, name), value);
}

void Shader::setVec2f(const char* name, float x, float y, bool useShader) {
	if (useShader) use();
	glUniform2f(glGetUniformLocation(m_ID, name), x, y);
}

void Shader::setVec2f(const char* name, const glm::vec2& value, bool useShader) {
	if (useShader) use();
	glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}

void Shader::setVec3f(const char* name, float x, float y, float z, bool useShader) {
	if (useShader) use();
	glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
}

void Shader::setVec3f(const char* name, const glm::vec3& value, bool useShader) {
	if (useShader) use();
	glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}

void Shader::setVec4f(const char* name, float x, float y, float z, float w, bool useShader) {
	if (useShader) use();
	glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
}

void Shader::setVec4f(const char* name, const glm::vec4& value, bool useShader) {
	if (useShader) use();
	glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMat2(const char* name, const glm::mat2& matrix, bool useShader) {
	if (useShader) use();
	glUniformMatrix2fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::setMat3(const char* name, const glm::mat3& matrix, bool useShader) {
	if (useShader) use();
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::setMat4(const char* name, const glm::mat4& matrix, bool useShader) {
	if (useShader) use();
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::m_checkCompileErrors(unsigned int object, std::string type) {

	int success{};
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			fmt::print(
				"| ERROR::SHADER: Compile-time error: Type: {}\n{}\n-----------------------------------\n",
				type, infoLog);
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 1024, nullptr, infoLog);
				fmt::print(
					"| ERROR::SHADER: Link-time error: Type: {}\n{}\n-----------------------------------\n",
					type, infoLog);
			}
		}
	}

}
