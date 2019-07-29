#version 330 core
layout(location = 0) in vec2 VertexPos;
layout(location = 1) in vec2 TextureCoords;

out vec2 TextCoords;

void main(){
	gl_Position = vec4(VertexPos, 0.0f, 1.0f);
	TextCoords = TextureCoords;
}