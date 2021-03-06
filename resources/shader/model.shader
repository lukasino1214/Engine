#shader vertex
#version 450
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 450 core
layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    color = texture(texture_diffuse1, TexCoords);
    color2 = 50;
}