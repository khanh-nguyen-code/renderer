#include"renderer.h"

namespace renderer {
index_buffer::index_buffer(){
	ASSERT(sizeof(uint32_t) == sizeof(GLuint));
	glGenBuffers(1, &m_renderer_id);
}
index_buffer::~index_buffer() {
	glDeleteBuffers(1, &m_renderer_id);
}

void index_buffer::update(const uint32_t *data, uint32_t count) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
	m_count = count;
}
void index_buffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}
void index_buffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}
