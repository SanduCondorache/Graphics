#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos, 1.0f);
    ourColor = aColor;
    TexCoord = aTextCoord;
};

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float t_Value;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main() {
    vec4 texColor = mix(texture(u_Texture2, TexCoord), texture(u_Texture1, TexCoord), 0.4f);
    FragColor = texColor;
}