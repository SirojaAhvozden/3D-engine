#version 330 core

in vec3 Color;
in vec2 TexCor;
in vec3 Normal;
in vec3 FragPos;

in vec3 Ambient;

out vec4 resultColor;

uniform sampler2D tex;

void main(){

	vec3 totalLight = (Ambient);
    
    vec3 color = Color * totalLight;
	
	if (TexCor.x < -1.f){
        resultColor = vec4(color, 1.f);
    } else {
        resultColor = texture(tex, TexCor) * vec4(color, 1.f);
    }
	
    // Выходной цвет = цвету текстуры в указанных UV-координатах
    
}
