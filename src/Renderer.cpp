#include"renderer.h"

namespace renderer {
void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::Draw(const vertex_array& va, const index_buffer& ib, const shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}
}
