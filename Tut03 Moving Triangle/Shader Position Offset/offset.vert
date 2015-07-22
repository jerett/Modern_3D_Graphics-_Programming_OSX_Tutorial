#version 330

layout(location=0) in vec4 position;

uniform vec2 offset;

void main()
{
    vec4 offset_vec4 = vec4(offset.x, offset.y, 0, 0);
    gl_Position = position + offset_vec4;
}
