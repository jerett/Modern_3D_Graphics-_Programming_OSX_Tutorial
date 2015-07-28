#include <opengl/gl3.h>
#include <vector>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "framework/framework.h"

const float vertex_positions[] = 
{
    0.25f,  0.25f, 0.75f, 1.0f,
    0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f,  0.25f, 0.75f, 1.0f,

    0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f,  0.25f, 0.75f, 1.0f,

    0.25f,  0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,
    0.25f, -0.25f, -0.75f, 1.0f,

    0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,

    -0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f, -0.25f,  0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,

    -0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,

    0.25f,  0.25f,  0.75f, 1.0f,
    0.25f, -0.25f, -0.75f, 1.0f,
    0.25f, -0.25f,  0.75f, 1.0f,

    0.25f,  0.25f,  0.75f, 1.0f,
    0.25f,  0.25f, -0.75f, 1.0f,
    0.25f, -0.25f, -0.75f, 1.0f,

    0.25f,  0.25f, -0.75f, 1.0f,
    0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f,  0.25f,  0.75f, 1.0f,

    0.25f,  0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,

    0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f,  0.75f, 1.0f,
    0.25f, -0.25f,  0.75f, 1.0f,

    0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f,  0.75f, 1.0f,


    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,

    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

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
GLuint loop_duration_location;
GLuint time_location;

void
initProgram()
{
    std::vector<GLuint> shaders;
    shaders.push_back(Framework::CreateShader(GL_VERTEX_SHADER, "offset.vert"));
    shaders.push_back(Framework::CreateShader(GL_FRAGMENT_SHADER, "offset.frag"));

    program = Framework::CreateProgram(shaders);

    loop_duration_location = glGetUniformLocation(program, "loopDuration");
    time_location = glGetUniformLocation(program, "time");

    glUseProgram(program);
    glUseProgram(0);

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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
}

void
Render(GLFWwindow *window)
{
    glClearColor(0.0, 0.0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    size_t colorData = sizeof(vertex_positions) /2;
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);

    glDrawArrays(GL_TRIANGLES, 0, 6*2*3);

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(window);
}

void
defaults(int& width, int& height)
{
    width = 500;
    height = 500;
}
