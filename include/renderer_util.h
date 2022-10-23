#ifndef __RENDERER_UTIL_H__
#define __RENDERER_UTIL_H__
#include<tuple>
#include<string>

namespace renderer_util {
std::tuple<std::string, std::string> parse_shader(const std::string& path);

}

#endif // __RENDERER_UTIL_H__