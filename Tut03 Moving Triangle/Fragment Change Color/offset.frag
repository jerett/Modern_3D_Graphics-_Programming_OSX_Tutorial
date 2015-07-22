#version 330

out vec4 outputColor;

uniform float time;
uniform float loopDuration;

void main()
{
    vec4 color1 = vec4(1, 0, 0, 1.0);
    vec4 color2 = vec4(0, 1, 0, 1);
    float lerp = mod(time, loopDuration) / loopDuration;
    outputColor = mix(color1, color2, lerp);
}
