#version 330 core

in vec2 texCor;

out vec4 color;

uniform sampler2D tex;

void main(){

    color = texture(tex, texCor);
	//color = vec4(outColor, 1.0f);
}