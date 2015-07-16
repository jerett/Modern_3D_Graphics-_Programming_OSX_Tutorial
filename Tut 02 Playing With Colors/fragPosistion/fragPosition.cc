#include "framework/framework.h"
#include <opengl/gl3.h>
#include <vector>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const float vertex_positions[] = 
{
    -0.75, -0.75, 0, 1.0,
    0.75,  -0.75, 0, 1.0,
    0.75,  0.75,  0, 1.0,
};

GLuint position_buffer_object;
void
initVertexBuffer()
{
    glGenBuffers(1, &position_buffer_object);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint program;
void
initProgram()
{
    std::vector<GLuint> shaders;
    shaders.push_back(Framework::CreateShader(GL_VERTEX_SHADER, "fragPosition.vert"));
    shaders.push_back(Framework::CreateShader(GL_FRAGMENT_SHADER, "fragPosition.frag"));
    program = Framework::CreateProgram(shaders);
    for(auto shader : shaders)
    {
        glDeleteShader(shader);
    }
}

GLuint vao;
void
init()
{
    initVertexBuffer();
    initProgram();
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void
Render(GLFWwindow *window)
{
    glClearColor(1.0, 0.0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT,GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
}

void
defaults(int& width, int& height)
{
    width = 500;
    height = 500;
}

