#include "framework.h"
#include <opengl/gl3.h>
#include <sstream>
#include <iostream>
#include <fstream>

namespace Framework
{
    std::string 
        fileData(const std::string& path)
        {
            std::ifstream shader_file(path);
            if(!shader_file.is_open())
            {
                throw std::runtime_error("shader open failed at " + path);
            }
            std::stringstream shader_stream;
            shader_stream << shader_file.rdbuf();
            return shader_stream.str();
        }

    GLuint 
        CreateShader(GLenum type, const std::string& path)
        {
            const std::string shader_data(fileData(path));

            GLuint shader = glCreateShader(type);
            const char *shader_content_cstr = shader_data.c_str();
            glShaderSource(shader, 1, &shader_content_cstr, 0);
            glCompileShader(shader);

            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

                GLchar *strInfoLog = new GLchar[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

                const char *strShaderType = NULL;
                switch(type)
                {
                    case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
                    case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
                }

                fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
                delete[] strInfoLog;

            }
            return shader;
        }

    GLuint
        CreateProgram(const std::vector<GLuint>& shaders)
        {
            GLuint program = glCreateProgram();
            for(auto shader : shaders)
            {
                glAttachShader(program, shader);
            }
            glLinkProgram(program);

            GLint status;
            glGetProgramiv(program, GL_COMPILE_STATUS, &status);

            if(status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

                GLchar *strInfoLog = new GLchar[infoLogLength + 1];
                glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

                const char *strShaderType = NULL;
                fprintf(stderr, "link failure in %s shader:\n%s\n", strShaderType, strInfoLog);
                delete[] strInfoLog;
            }

            for(GLuint shader : shaders)
            {
                glDetachShader(program, shader);
            }
            return program;
        }

};

void init();
void Render(GLFWwindow *window);
void defaults(int &width, int &height);

void
err_callback(int err_code ,const char *description )
{
    std::cerr << description << std::endl;
}

int main(int argc, char *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwSetErrorCallback(err_callback);
    int width = 800;
    int height = 600;
    defaults(width, height);

    GLFWwindow* window = glfwCreateWindow(width, height, argv[0], NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    init();

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        Render(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
