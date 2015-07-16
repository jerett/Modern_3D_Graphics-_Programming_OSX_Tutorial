#include <opengl/gl3.h>
#include <string>
#include <vector>
#include <iostream>
#include "framework/framework.h"

GLuint 
createShader(GLenum file_type, const std::string &shader_content) 
{
    GLuint shader = glCreateShader(file_type);
    const char *shader_content_cstr = shader_content.data();
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
        switch(file_type)
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
createProgram(std::vector<GLuint> shaders)
{
    GLuint program = glCreateProgram();

    for(GLuint shader : shaders)
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

GLuint program;
const std::string vertex_shader(
        "#version 330 \n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = position;\n"
        "}\n"
        );

const std::string fragment_shader(
        "#version 330 \n"
        "out vec4 outputColor;\n"
        "void main()\n"
        "{\n"
        "outputColor = vec4(0.0, 1.0, 0.0, 1.0);"
        "}\n"
        );

void
initializeProgram()
{
    std::vector<GLuint> shaders;
    shaders.push_back(createShader(GL_VERTEX_SHADER, vertex_shader));
    shaders.push_back(createShader(GL_FRAGMENT_SHADER, fragment_shader));

    program = createProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}

GLuint position_buffer_object;
const float vertex_positions[] = 
{
    -1.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    -1.0, 0.0, 0.0, 1.0,

    1.0, -1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    0.0, -1.0, 0.0, 1.0
};
void
initializeVertexBuffer()
{
    glGenBuffers(1, &position_buffer_object);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    //unbind GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

GLuint vao;
void
init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    initializeProgram();
    initializeVertexBuffer();
}

void
Render(GLFWwindow *window)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glUseProgram(0); 

    glfwSwapBuffers(window);
}

void
defaults(int &width, int &height)
{
    width = 500;
    height = 500;
}

/*
void
err_callback(int err_code ,const char *description )
{
    std::cerr << description << std::endl;
}

int
main(int argc, char *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwSetErrorCallback(err_callback);
    GLFWwindow* window = glfwCreateWindow(800, 600, argv[0], NULL, NULL);
    glfwMakeContextCurrent(window);
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
*/
