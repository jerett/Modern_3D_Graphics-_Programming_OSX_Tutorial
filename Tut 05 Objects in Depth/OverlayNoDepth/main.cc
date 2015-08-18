#include "framework/framework.h"
#include <opengl/gl3.h>

#define RIGHT_EXTENT 0.8f
#define LEFT_EXTENT -RIGHT_EXTENT
#define TOP_EXTENT 0.2f
#define MIDDLE_EXTENT 0.0f
#define BOTTOM_EXTENT -TOP_EXTENT
#define FRONT_EXTENT -1.25f
#define REAR_EXTENT -1.75f

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR  0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f
//#define FRONT_EXTENT 0
//#define REAR_EXTENT 0

const float vertex_positions[] = 
{
    //object 1
    LEFT_EXTENT, TOP_EXTENT, REAR_EXTENT,
    LEFT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,

    RIGHT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
    RIGHT_EXTENT, TOP_EXTENT, REAR_EXTENT,

    LEFT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,
    LEFT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,

    RIGHT_EXTENT, BOTTOM_EXTENT, REAR_EXTENT,
    RIGHT_EXTENT, MIDDLE_EXTENT, FRONT_EXTENT,

    //object 2
    TOP_EXTENT, RIGHT_EXTENT, REAR_EXTENT, 
    MIDDLE_EXTENT, RIGHT_EXTENT, FRONT_EXTENT,

    MIDDLE_EXTENT, LEFT_EXTENT, FRONT_EXTENT,
    TOP_EXTENT, LEFT_EXTENT, REAR_EXTENT,

    MIDDLE_EXTENT, RIGHT_EXTENT, FRONT_EXTENT,
    BOTTOM_EXTENT, RIGHT_EXTENT, REAR_EXTENT,

    BOTTOM_EXTENT, LEFT_EXTENT, REAR_EXTENT,
    MIDDLE_EXTENT, LEFT_EXTENT, FRONT_EXTENT,
    
    
    GREEN_COLOR,
    GREEN_COLOR,
    GREEN_COLOR,
    GREEN_COLOR,

    BROWN_COLOR,
    BROWN_COLOR,
    BROWN_COLOR,
    BROWN_COLOR,

    //color for object2
    RED_COLOR,
    RED_COLOR,
    RED_COLOR,
    RED_COLOR,


    BLUE_COLOR,
    BLUE_COLOR,
    BLUE_COLOR,
    BLUE_COLOR,
};

const GLshort index_data[] = 
{
    //first object
    0, 2, 1,
    0, 3, 2,

    4, 6, 5,
    4, 7, 6,
}; 

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

    float scale = 1.0;
    float z_near = 1;
    float z_far = 3;
    float matrix[4][4] = {};
    matrix[0][0] = scale;
    matrix[1][1] = scale;
    matrix[2][2] = (z_near + z_far) / (z_near - z_far);
    matrix[2][3] = 2 * z_far * z_near / (z_near - z_far);
    matrix[3][2] = -1;

    glUseProgram(program);
    glUniformMatrix4fv(matrix_location, 1, GL_TRUE, &matrix[0][0]);
    glUniform3f(offset_location, 0, 0, 0);
    glUseProgram(0);


    for(auto shader : shaders)
    {
        glDeleteShader(shader);
    }
}

GLuint position_buffer_object;
GLuint index_buffer_object;
GLuint vao, vao1;

const int num_count = 8;
void
initVertexBuffer()
{
    glGenBuffers(1, &position_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glGenBuffers(1, &index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    size_t color_offset = sizeof(float) * 3 * num_count * 2 ;

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

    glBindVertexArray(0);

    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    size_t vertex_offset = sizeof(float) * 3 * num_count;
    color_offset = sizeof(float) * 3 * num_count * 2 + sizeof(float) * 4 * num_count;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)vertex_offset);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

    glBindVertexArray(0);
}

void
init()
{
    initProgram();
    initVertexBuffer();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
}

void
Render(GLFWwindow *window)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, sizeof(index_data), GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    glBindVertexArray(vao1);
    glDrawElements(GL_TRIANGLES, sizeof(index_data), GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
    
    glfwSwapBuffers(window);
}

void
defaults(int &width, int &height)
{
    width = 500;
    height = 500;
}
