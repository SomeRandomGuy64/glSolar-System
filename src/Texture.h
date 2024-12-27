#pragma once

#include <glad/glad.h>

class Texture {

public:
	Texture();

	void generate(unsigned int width, unsigned int height, unsigned char* data);
	void bind() const;

	unsigned int& getIdRef();

	void setInternalFormat(unsigned int internalFormat);
	void setImageFormat(unsigned int imageFormat);

private:
	unsigned int m_ID{};

	unsigned int m_width{};
	unsigned int m_height{};

	unsigned int m_internalFormat{};
	unsigned int m_imageFormat{};

	unsigned int m_wrapS{};
	unsigned int m_wrapT{};
	unsigned int m_filterMin{};
	unsigned int m_filterMax{};

};
