#include"renderer/renderer.h"

namespace renderer {


uint32_t vertex_field_size(vertex_field field) {
    auto [type, count] = field;
    switch (type){
        case dtype::float32:    return 4 * count;
        case dtype::uint32:     return 4 * count;
        case dtype::uint8:      return 1 * count;
        default: return 0;
    }
}

uint32_t vertex_layout_size(const vertex_layout& layout) {
    uint32_t size = 0;
    for (auto& e: layout) {
        size += vertex_field_size(e);
    }
    return size;
}



vertex_buffer::vertex_buffer() {
	glGenBuffers(1, &m_renderer_id);
}

vertex_buffer::~vertex_buffer() {
	glDeleteBuffers(1, &m_renderer_id);
}
void vertex_buffer::update(const void *data, uint32_t count, const vertex_layout& layout) {
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ARRAY_BUFFER, count * vertex_layout_size(layout), data, GL_STATIC_DRAW);
	m_layout = layout;
}
void vertex_buffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}
void vertex_buffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}