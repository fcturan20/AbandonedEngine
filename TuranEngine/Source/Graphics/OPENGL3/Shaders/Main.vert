#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TextureCoord;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 Bitangent;


out vec2 TextCoord;


uniform mat4 world_transform;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;


void main()
{
	TextCoord = TextureCoord;
    gl_Position = projection_matrix * view_matrix * vec4(Position, 1.0);
}
