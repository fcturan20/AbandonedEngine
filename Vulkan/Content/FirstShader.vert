#version 450
vec2 positions[3] = vec2[](vec2(0.0,-0.5f), vec2(-0.5f, 0.5f), vec2(0.5f, 0.5f));
void main(){
	gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0f);
}