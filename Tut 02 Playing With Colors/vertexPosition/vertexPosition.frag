#version 330

out vec4 outputColor;
in  vec4 theColor;

void main()
{
    /*float scale = gl_FragCoord.y / 600;*/
    /*outputColor = mix(vec4(0,1,0,1), vec4(0.2, 0.2, 0.2,1), scale);*/
    /*outputColor = theColor * scale;*/

    outputColor = theColor;
}
