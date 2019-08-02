#version 330 core
out vec4 Fragment_Color;

in vec2 TextCoord;


uniform sampler2D texture_diffuse;

float LinearizeDepth(float depth) 
{
	float near = 0.1; 
	float far  = 10000.0; 

    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {
	//float depth = LinearizeDepth(gl_FragCoord.z) / far;
	//gl_FragDepth = depth;

	//Final Fragment Color
	//Fragment_Color = vec4(normal, 1.0f);
	vec4 object_color = texture(texture_diffuse, TextCoord);
	Fragment_Color = vec4(object_color.rgb, 1);
	//Fragment_Color = vec4(TextCoord, 0 ,0);
	//Fragment_Color = vec4(depth);

}
