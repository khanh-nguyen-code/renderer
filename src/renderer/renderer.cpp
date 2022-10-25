#include"renderer/renderer.h"

namespace renderer {
void renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void renderer::draw(const vertex_array& va, const index_buffer& ib, const shader& shader) const {
	shader.bind();
	va.bind();
	ib.bind();
	glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}
}
