#ifndef __RENDERER_H__
#define __RENDERER_H__

#include<vector>
#include<string>
#include<unordered_map>
#include<GL/glew.h>

#define ASSERT(x) if (!(x)) __builtin_trap()

namespace renderer {
enum dtype {
    float32 = GL_FLOAT,
    uint32 = GL_UNSIGNED_INT,
    uint8 = GL_UNSIGNED_BYTE
};


class texture{
public:
    enum color {r8 = 0, rgb8 = 1, rgba8 = 2};
    texture();
    ~texture();

    void update(unsigned char* buffer, int height, int width, color color = r8) const;
    void bind(uint32_t slot=0) const;
    void unbind(uint32_t slot=0) const;
private:
    uint32_t m_renderer_id;
};
class shader {
public:
    shader(const std::string& v_shader, const std::string& f_shader);
    ~shader();

    void bind() const;
    void unbind() const;

    //set uniform	
    void set_uniform_1i(const std::string& name, int value);
    void set_uniform_1f(const std::string& name, float value);
    void set_uniform_4f(const std::string& name, float f0, float f1, float f2, float f3);
private:
    uint32_t create_shader();
    uint32_t compile_shader(uint32_t type);
    int get_uniform_location(const std::string& name);
private:
    uint32_t m_renderer_id;
    std::string m_vertex_shader;
    std::string m_fragment_shader;
    std::unordered_map<std::string, int> m_uniform_location_cache;
};
class index_buffer {
public:
    index_buffer();
    ~index_buffer();

    // count : number of elements
    void update(const uint32_t *data, uint32_t count);

    void bind() const;
    void unbind() const;

    inline uint32_t count() const {return m_count;}
private:
    uint32_t m_renderer_id;
    uint32_t m_count;
};

struct vertex_field {
	uint32_t type;
	uint32_t count;
};
uint32_t vertex_field_size(vertex_field field);

using vertex_layout = std::vector<vertex_field>;
uint32_t vertex_layout_size(const vertex_layout& layout);

class vertex_buffer{
public:
    vertex_buffer();
    ~vertex_buffer();

    // size : size in bytes of data
    void update(const void *data, uint32_t size, const vertex_layout& layout);
    inline const vertex_layout& layout() const {return m_layout;}
    void bind() const;
    void unbind() const;
private:
    uint32_t m_renderer_id;
    vertex_layout m_layout;
};


class vertex_array{
public:
    vertex_array();
    ~vertex_array();

    void add_buffer(const vertex_buffer& vb);
    void bind() const;
    void unbind() const;
private:
    uint32_t m_renderer_id;
};
class renderer {
public:
    void clear();
    void draw(const vertex_array& va, const index_buffer& ib, const shader& shader) const;
};
}

#endif // __RENDERER_H__