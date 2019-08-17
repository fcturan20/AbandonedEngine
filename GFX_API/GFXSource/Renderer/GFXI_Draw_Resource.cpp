#include "GFXI_Draw_Resource.h"


unsigned int GFXI_Draw_Resource::Find_ShaderID_byName(string shader_name) {
	return GFX_Shader::Find_Shader_byName(shader_name)->PROGRAM_ID;
}


void GFXI_Draw_Resource::Clean_Resource() {

}