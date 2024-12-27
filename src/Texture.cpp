#include "texture.h"

Texture::Texture()
	: m_internalFormat(GL_RGB)
	, m_imageFormat(GL_RGB)
	, m_wrapS(GL_REPEAT)
	, m_wrapT(GL_REPEAT)
	, m_filterMin(GL_LINEAR)
	, m_filterMax(GL_LINEAR)
{
	glGenTextures(1, &m_ID);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char* data) {
	m_width = width;
	m_height = height;

	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

unsigned int& Texture::getIdRef() {
	return m_ID;
}

void Texture::setInternalFormat(unsigned int internalFormat) {
	m_internalFormat = internalFormat;
}

void Texture::setImageFormat(unsigned int imageFormat) {
	m_imageFormat = imageFormat;
}