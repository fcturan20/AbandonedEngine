#version 330 core
out vec4 Fragment_Color;

float near = 0.1; 
float far  = 1000.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	gl_FragDepth = depth;

	//Final Fragment Color
	//Fragment_Color = vec4(normal, 1.0f);
	Fragment_Color = vec4(gl_FragDepth);
	//Fragment_Color = vec4(depth);

}
