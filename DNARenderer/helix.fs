#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform bool invertColor;

void main()
{    
    vec4 color = texture(texture_diffuse1, TexCoords);

    if (invertColor)
    {
        color = vec4(1.0 - color.rbg, color.a);
    }
    FragColor = color;
}