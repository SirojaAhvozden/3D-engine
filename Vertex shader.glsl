#version 330 core

// ¬ходные данные вершин, различные дл€ всех запусков этого шейдера
layout(location = 0) in vec3 position;
//layout(location = 1) in vec2 textureCoor;

//out vec2 texCor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main(){

    // ¬ыходна€ позици€ вершины
    gl_Position = projection * view * transform * vec4(position, 1.0f);
   // texCor = textureCoor;
}