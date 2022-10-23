#include"renderer.h"
namespace renderer {
vertex_array::vertex_array() {
	glGenVertexArrays(1, &m_renderer_id);
}
vertex_array::~vertex_array() {
	glDeleteVertexArrays(1, &m_renderer_id);
}
void vertex_array::add_buffer(const vertex_buffer& vb) {
	bind();
	vb.bind();
	uint32_t stride = 0;
	for (auto& e: vb.layout()) {
		stride += e.size();
	}
	unsigned int offset = 0;
	for (unsigned int i=0; i<vb.layout().size(); i++) {
		const auto& e = vb.layout()[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, e.count, e.type,  GL_FALSE , stride, reinterpret_cast<const void*>(offset));
		offset += e.size();
	}
}
void vertex_array::bind() const {
	glBindVertexArray(m_renderer_id);
}
void vertex_array::unbind() const {
	glBindVertexArray(0);
}
}
