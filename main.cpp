#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"renderer.h"
#include"renderer_util.h"
#include"stb_image.h"
#include"include/shaders/image2d.h"
#include"timer.h"

#include<random>

class texture_buffer {
public:
	texture_buffer(const std::string& path) {
		stbi_set_flip_vertically_on_load(1);
		buffer = stbi_load("./data/textures/image.png", &width, &height, &chan, 4);
		engine = std::default_random_engine();		
	}
	unsigned char* next() {
		std::uniform_int_distribution<uint8_t> dist(0, 255);
		for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
		for (int k=0; k<chan; k++) {
			if (i < height/2)
				buffer[(i * width + j) * chan + k] = dist(engine);
		}
		return buffer;
	}	

	~texture_buffer() {
		stbi_image_free(buffer);
	}
	std::default_random_engine engine;
	int width, height, chan;
	unsigned char* buffer;
};


int main(void) {
	//intialize the library
	if (!glfwInit())
		return -1;

	const int window_width = 640;
	const int window_height = 480;

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		std::cout << "error" << std::endl;
	}

	std::cout << "opengl version: " << glGetString(GL_VERSION) << std::endl;

	std::vector<renderer::vertex_buffer> vb_list;
	{
		std::vector<float> positions = {
			-1.0f, -1.0f, 0.0f, 0.0f, // bottom left
			1.0f, -1.0f, 1.0f, 0.0f, // bottom right
			1.0f,  1.0f, 1.0f, 1.0f, // top right
			-1.0f,  1.0f, 0.0f, 1.0f  // top left
		};
		// 2 floats of rectangle vertices
		// 2 floats of texture coordinates
		vb_list.emplace_back();
		vb_list.back().update(
			positions.data(), positions.size() * sizeof(float),
			{{renderer::float32, 2}, {renderer::float32, 2}} 
		);
	}

	renderer::vertex_array va;
	{
		for (auto& vb: vb_list) {
			va.add_buffer(vb);
		}

	}
	
	renderer::index_buffer ib;
	{
		std::vector<uint32_t> indices = {
			0, 1, 2, // first triangle (bottom left - bottom right - top right)
			2, 3, 0  // second triangle (top right - top left - bottom left)
		};
		ib.update(indices.data(), indices.size());
	}
	
	const std::string source(reinterpret_cast<char*>(&shader::image2d[0]), shader::image2d_len);
	auto [v_shader, f_shader] = renderer_util::parse_shader(source);
	renderer::shader shader(v_shader, f_shader);
	
	renderer::texture texture;
	
	renderer::renderer renderer;

	texture_buffer image("./data/textures/image.png");

	uint64_t dt = 0;
	uint64_t t1, t2;

	while (!glfwWindowShouldClose(window)) {
		t1 = timer::now();
		/* render here */
		renderer.clear();

		shader.bind();
		
		texture.update(image.next(), image.height, image.width, renderer::texture::color::rgba8);
		texture.bind();
		shader.set_uniform_1i("u_Texture", 0);

		va.bind();
		ib.bind();

		renderer.draw(va, ib, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
		t2 = timer::now();
		dt = 0.9 * dt + 0.1 * (t2-t1);
		double fps = 1 / (static_cast<double>(dt) / 1000000000);
		std::cout << "fps: " << fps << std::endl;
	}
	
	glfwTerminate();
	return 0;
}
