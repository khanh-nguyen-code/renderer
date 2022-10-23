#include<tuple>
#include<fstream>
#include<sstream>

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
}