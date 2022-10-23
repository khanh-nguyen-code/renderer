#include"renderer.h"
namespace renderer {
texture::texture(unsigned char* image, int height, int width, color color) {
	glGenTextures(1, &m_renderer_id);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);

		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	GLint internal_format;
	GLenum format;
	switch (color)
	{
	case color::r8:
		internal_format = GL_RED;
		format = GL_RED;
		break;
	case color::rgb8:
		internal_format = GL_RGB8;
		format = GL_RGB;
		break;
	case color::rgba8:
		internal_format = GL_RGBA8;
		format = GL_RGBA;
		break;
	
	default:
		internal_format = GL_RED;
		format = GL_RED;
		break;
	}


	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
texture::~texture() {
	glDeleteTextures(1, &m_renderer_id);
}

void texture::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}
void texture::unbind(unsigned int slot) const {
	glBindTexture(GL_TEXTURE_2D, 0);
}
}
