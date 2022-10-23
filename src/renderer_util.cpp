#include<tuple>
#include<fstream>
#include<sstream>
#include<vector>
#include"renderer_util.h"
#include"renderer.h"
#include"shader.h"

namespace renderer_util {
std::tuple<std::string, std::string> parse_shader(const std::string& source) {
    std::istringstream stream(source);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    std::string line;
    std::stringstream s[2];
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            s[int(type)] << line << "\n";
        }
    }
    return {s[0].str(), s[1].str()};
}
/*
class window {
public:
    enum color {r8, rgb8, rgba8};
    window(int width, int height, const std::string& name);
    ~window();
    void update(unsigned char *buffer, int height, int width, color color = r8);
};
*/
window::window(int width, int height, const std::string& name) {
    m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        std::exit(1);
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        std::exit(1);
    }

	std::vector<float> positions = {
		-1.0f, -1.0f, 0.0f, 0.0f, // bottom left
		 1.0f, -1.0f, 1.0f, 0.0f, // bottom right
		 1.0f,  1.0f, 1.0f, 1.0f, // top right
		-1.0f,  1.0f, 0.0f, 1.0f  // top left
	};



	renderer::vertex_array va;
	renderer::vertex_buffer vb;
	vb.update(positions.data(), positions.size() * sizeof(float));
	renderer::vertex_buffer_layout layout;
	layout.push_float(2);// 2 floats of rectangle vertices
	layout.push_float(2);// 2 floats of texture coordinates

	va.add_buffer(vb, layout);

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
	renderer::index_buffer ib;
	ib.update(indices.data(), indices.size());
	
	const std::string source(reinterpret_cast<char*>(&shader[0]), shader_len);
	auto [v_shader, f_shader] = renderer_util::parse_shader(source);
	renderer::shader shader(v_shader, f_shader);
	shader.bind();

	renderer::texture texture;
	texture.bind();
	

	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();
	texture.unbind();

	renderer::renderer renderer;
}


}