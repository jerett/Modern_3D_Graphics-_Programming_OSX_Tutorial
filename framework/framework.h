#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <vector>
#include <string>
#include <glfw/glfw3.h>


namespace Framework
{
    GLuint CreateShader(GLenum type, const std::string& path);
    GLuint CreateProgram(const std::vector<GLuint>& shaders);
};

#endif
