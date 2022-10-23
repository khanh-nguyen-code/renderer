#include"renderer.h"
namespace renderer {
unsigned int vertex_buffer_field::size() const {
	switch (type){
		case GL_FLOAT:			return 4 * count;
		case GL_UNSIGNED_INT:	return 4 * count;
		case GL_UNSIGNED_BYTE:	return 1 * count;
		default: return 0;
	}
}

void vertex_buffer_layout::push_float(unsigned int count) {
	m_element_list.push_back( {GL_FLOAT, count} );
	m_stride += m_element_list.back().size();
}
void vertex_buffer_layout::push_unsigned_int(unsigned int count) {
	m_element_list.push_back( {GL_UNSIGNED_INT, count} );
	m_stride += m_element_list.back().size();
}
void vertex_buffer_layout::push_unsigned_char(unsigned int count) {
	m_element_list.push_back( {GL_UNSIGNED_BYTE, count} );
	m_stride += m_element_list.back().size();
}
}
