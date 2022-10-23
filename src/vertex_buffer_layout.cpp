#include"renderer.h"
namespace renderer {
unsigned int vertex_buffer_element::size() const {
	switch (type){
		case GL_FLOAT:			return 4 * count;
		case GL_UNSIGNED_INT:	return 4 * count;
		case GL_UNSIGNED_BYTE:	return 1 * count;
		default: return 0;
	}
}

void vertex_buffer_layout::push_float(unsigned int count) {
	m_element_list.push_back( {GL_FLOAT, count, GL_FALSE} );
	m_stride += m_element_list.back().size();
}
void vertex_buffer_layout::push_unsigned_int(unsigned int count) {
	m_element_list.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
	m_stride += m_element_list.back().size();
}
void vertex_buffer_layout::push_unsigned_char(unsigned int count) {
	m_element_list.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE} );
	m_stride += m_element_list.back().size();
}
}
