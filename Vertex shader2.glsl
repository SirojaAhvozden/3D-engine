#version 330 core

// ¬ходные данные вершин, различные дл€ всех запусков этого шейдера
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 clr;
layout(location = 2) in vec2 texCor;
layout(location = 3) in vec3 normalVec;

out vec3 Color;
out vec2 TexCor;
out vec3 Normal;
out vec3 FragPos;

out vec3 Ambient;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 ambient;

void main(){

    // ¬ыходна€ позици€ вершины
    gl_Position = projection * view * transform * vec4(position, 1.0f);
    Color = clr;
    TexCor = texCor;

	Ambient = ambient;

    Normal = normalVec;
}