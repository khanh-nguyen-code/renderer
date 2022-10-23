#ifndef __RENDERER_UTIL_H__
#define __RENDERER_UTIL_H__
#include<tuple>
#include<string>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace renderer_util {
std::tuple<std::string, std::string> parse_shader(const std::string& path);
class window {
public:
    enum color {r8, rgb8, rgba8};
    window(int width, int height, const std::string& name);
    ~window();
    void update(unsigned char *buffer, int height, int width, color color = r8);
private:
    GLFWwindow* m_window;

};
}

#endif // __RENDERER_UTIL_H__