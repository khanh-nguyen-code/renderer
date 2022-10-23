#include"renderer.h"

namespace renderer {
vertex_buffer::vertex_buffer() {
	glGenBuffers(1, &m_renderer_id);
}

vertex_buffer::~vertex_buffer() {
	glDeleteBuffers(1, &m_renderer_id);
}
void vertex_buffer::update(const void *data, unsigned int size, const std::vector<vertex_buffer_field>& layout) {
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	m_layout = layout;
}
void vertex_buffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}
void vertex_buffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}