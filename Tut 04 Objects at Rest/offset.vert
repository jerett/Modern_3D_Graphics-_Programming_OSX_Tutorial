#version 330

layout(location=0) in vec4 position;

uniform float time;
uniform float loopDuration;

void main()
{
    float scale = 3.14159f * 2.0f / 5.0;
    float degree = mod(time ,loopDuration) * scale;
    vec4 offset_vec4 = vec4(
            cos(degree) * 0.5,
            sin(degree) * 0.5,
            0,
            0);
    gl_Position = position + offset_vec4;
    /*gl_Position = position;*/
}
