#version 330 core
out vec4 Fragment_Color;

in vec2 TextCoord;



uniform sampler2D texture_diffuse;

void main() {
	//float depth = LinearizeDepth(gl_FragCoord.z) / far;
	//gl_FragDepth = depth;

	//Final Fragment Color
	//Fragment_Color = vec4(normal, 1.0f);
	vec4 object_color = texture(texture_diffuse, TextCoord);
	//if(object_color.a < 0.5){
		//discard;
	//}

	//Fragment_Color = vec4(TextCoord, 0, 0);
	//Fragment_Color = vec4(TextCoord, 0 ,0);
	//Fragment_Color = vec4(depth);
	Fragment_Color = object_color;
}
