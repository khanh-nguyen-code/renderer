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
    void bind(unsigned int slot=0) const;
    void unbind(unsigned int slot=0) const;
private:
    unsigned int m_renderer_id;
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
    unsigned int create_shader();
    unsigned int compile_shader(unsigned int type);
    int get_uniform_location(const std::string& name);
private:
    unsigned int m_renderer_id;
    std::string m_vertex_shader;
    std::string m_fragment_shader;
    std::unordered_map<std::string, int> m_uniform_location_cache;
};
class index_buffer {
public:
    index_buffer();
    ~index_buffer();

    // count : number of elements
    void update(const unsigned int *data, unsigned int count);

    void bind() const;
    void unbind() const;

    inline unsigned int count() const {return m_count;}
private:
    unsigned int m_renderer_id;
    unsigned int m_count;
};
struct vertex_buffer_field {
	unsigned int type;
	unsigned int count;
    unsigned int size() const {
        switch (type){
            case dtype::float32:    return 4 * count;
            case dtype::uint32:     return 4 * count;
            case dtype::uint8:      return 1 * count;
            default: return 0;
        }
    }
};
class vertex_buffer{
public:
    vertex_buffer();
    ~vertex_buffer();

    // size : size in bytes of data
    void update(const void *data, unsigned int size, const std::vector<vertex_buffer_field>& layout);
    inline const std::vector<vertex_buffer_field>& layout() const {return m_layout;}
    void bind() const;
    void unbind() const;
private:
    unsigned int m_renderer_id;
    std::vector<vertex_buffer_field> m_layout;
};


class vertex_array{
public:
    vertex_array();
    ~vertex_array();

    void add_buffer(const vertex_buffer& vb);
    void bind() const;
    void unbind() const;
private:
    unsigned int m_renderer_id;
};
class renderer {
public:
    void clear();
    void draw(const vertex_array& va, const index_buffer& ib, const shader& shader) const;
};
}

#endif // __RENDERER_H__