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
    0.25f,  0.25f, -1.25f, 1.0f,
    0.25f, -0.25f, -1.25f, 1.0f,
    -0.25f,  0.25f, -1.25f, 1.0f,

    0.25f, -0.25f, -1.25f, 1.0f,
    -0.25f, -0.25f, -1.25f, 1.0f,
    -0.25f,  0.25f, -1.25f, 1.0f,

    0.25f,  0.25f, -2.75f, 1.0f,
    -0.25f,  0.25f, -2.75f, 1.0f,
    0.25f, -0.25f, -2.75f, 1.0f,

    0.25f, -0.25f, -2.75f, 1.0f,
    -0.25f,  0.25f, -2.75f, 1.0f,
    -0.25f, -0.25f, -2.75f, 1.0f,

    -0.25f,  0.25f, -1.25f, 1.0f,
    -0.25f, -0.25f, -1.25f, 1.0f,
    -0.25f, -0.25f, -2.75f, 1.0f,

    -0.25f,  0.25f, -1.25f, 1.0f,
    -0.25f, -0.25f, -2.75f, 1.0f,
    -0.25f,  0.25f, -2.75f, 1.0f,

    0.25f,  0.25f, -1.25f, 1.0f,
    0.25f, -0.25f, -2.75f, 1.0f,
    0.25f, -0.25f, -1.25f, 1.0f,

    0.25f,  0.25f, -1.25f, 1.0f,
    0.25f,  0.25f, -2.75f, 1.0f,
    0.25f, -0.25f, -2.75f, 1.0f,

    0.25f,  0.25f, -2.75f, 1.0f,
    0.25f,  0.25f, -1.25f, 1.0f,
    -0.25f,  0.25f, -1.25f, 1.0f,

    0.25f,  0.25f, -2.75f, 1.0f,
    -0.25f,  0.25f, -1.25f, 1.0f,
    -0.25f,  0.25f, -2.75f, 1.0f,

    0.25f, -0.25f, -2.75f, 1.0f,
    -0.25f, -0.25f, -1.25f, 1.0f,
    0.25f, -0.25f, -1.25f, 1.0f,

    0.25f, -0.25f, -2.75f, 1.0f,
    -0.25f, -0.25f, -2.75f, 1.0f,
    -0.25f, -0.25f, -1.25f, 1.0f,

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
GLuint offset_location;
GLuint matrix_location;

void
initProgram()
{
    std::vector<GLuint> shaders;
    shaders.push_back(Framework::CreateShader(GL_VERTEX_SHADER, "vertexShader.vert"));
    shaders.push_back(Framework::CreateShader(GL_FRAGMENT_SHADER, "fragmentShader.frag"));

    program = Framework::CreateProgram(shaders);

    offset_location = glGetUniformLocation(program, "offset");
    matrix_location = glGetUniformLocation(program, "perspectiveMatrix");


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
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    //glfwGetFramebufferSize(window, &width, &height);
    //std::cout << "width " << width << "height " << height << std::endl;

    glClearColor(0.0, 0.0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    float scale = 1.0;
    float z_near = 0.1;
    float z_far = 3;
    float matrix[4][4] = {0};
    matrix[0][0] = scale / (double(width) / height);
    matrix[1][1] = scale;
    matrix[2][2] = (z_near + z_far) / (z_near - z_far);
    matrix[2][3] = 2 * z_far * z_near / (z_near - z_far);
    matrix[3][2] = -1;

    glUniformMatrix4fv(matrix_location, 1, GL_TRUE, &matrix[0][0]);
    glUniform2f(offset_location, 0.5, 0.5);

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
