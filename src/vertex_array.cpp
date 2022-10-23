#include"renderer.h"
namespace renderer {
vertex_array::vertex_array() {
	glGenVertexArrays(1, &m_renderer_id);
}
vertex_array::~vertex_array() {
	glDeleteVertexArrays(1, &m_renderer_id);
}
void vertex_array::add_buffer(const vertex_buffer& vb, const vertex_buffer_layout& layout) {
	bind();
	vb.bind();
	const std::vector<vertex_buffer_element>& element_list = layout.element_list();
	unsigned int offset = 0;
	for (unsigned int i=0; i<element_list.size(); i++) {
		const auto& element = element_list[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,  element.normalized , layout.stride(), reinterpret_cast<const void*>(offset));
		offset += element.size();
	}
}
void vertex_array::bind() const {
	glBindVertexArray(m_renderer_id);
}
void vertex_array::unbind() const {
	glBindVertexArray(0);
}
}
