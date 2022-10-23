#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>


#include"renderer.h"
#include"renderer_util.h"
#include"stb_image.h"


#include<cmath>


int main(void)
{
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

	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	std::cout << "opengl version:" << glGetString(GL_VERSION) << std::endl;

	{


	std::vector<float> positions = {
		-1.0f, -1.0f, 0.0f, 0.0f, //bottom left
		 1.0f, -1.0f, 1.0f, 0.0f, //bottom right
		 1.0f,  1.0f, 1.0f, 1.0f, //top right
		-1.0f,  1.0f, 0.0f, 1.0f  //top left
	};



	renderer::vertex_array va;
	renderer::vertex_buffer vb(positions.data(), positions.size() * sizeof(float));
	renderer::vertex_buffer_layout layout;
	layout.push_float(2);// 2 floats of rectangle vertices
	layout.push_float(2);// 2 floats of texture coordinates

	va.add_buffer(vb, layout);

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
	renderer::index_buffer ib(indices.data(), indices.size());

	auto [v_shader, f_shader] = renderer_util::parse_shader("./data/shaders/image2d.shader");
	renderer::shader shader(v_shader, f_shader);
	shader.bind();


	int width, height, chan;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* image = stbi_load("./data/textures/image.png", &width, &height, &chan, 4);

	for (int i=0; i<height; i++)
	for (int j=0; j<width; j++)
	for (int k=0; k<chan; k++) {
		if (k == 2 and i < height/2)
			image[(i * width + j) * chan + k] = 255;
	}
	renderer::texture texture;
	texture.bind();
	

	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();
	texture.unbind();
	texture.update(image, height, width, renderer::texture::color::rgba8);

	renderer::renderer renderer;
	
	

	
	while (!glfwWindowShouldClose(window)) {
		/* render here */
		renderer.clear();

		shader.bind();
		
		texture.bind();
		shader.set_uniform_1i("u_Texture", 0);

		va.bind();
		ib.bind();

		renderer.draw(va, ib, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	}

	glfwTerminate();
	return 0;
}
