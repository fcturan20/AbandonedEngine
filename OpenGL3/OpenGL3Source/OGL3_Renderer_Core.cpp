#include "OGL3_Renderer_Core.h"
using namespace TuranAPI::File_System;


void OGL3_Renderer::Start_Creation() {
	//Compile all shader at Creation() because we don't want to get OpenGL initialization errors
	cout << "Compiled all shaders!\n\n";
	Send_Textures_to_GPU(&TuranAPI::File_System::Texture_Resource::ALL_TEXTUREs);
	cout << "Send textures to GPU!\n\n";
	/*
	//Create render source (Framebuffer etc.) of every draw pass for each scene!
	for (Scene* SCENE : Scene::ALL_SCENEs) {
		//Create RenderGraph of the Scene and give Scene* to RenderGraph because RenderGraph should access to Scene's MODELs, CAMERAs
		Create_RenderGraph(SCENE->Get_RenderGraph_type_Index(), SCENE);
		GFX_RenderGraph* RenderGraph = (GFX_RenderGraph*)SCENE->Return_RenderGraph();
		RenderGraph->Create_RenderGraph_Resources();
	}
	*/
	cout << "RenderGraph Creation and Start_Creation() is finished!\n";
}

//Note: To display someting on windows, we should MakeCurrentContext(window) and BindFramebuffer(0) for each one of them!
//Because a window's default display framebuffer is 0
//After BindFramebuffer(0), you should render a quad with sending the render target you want to display
//After rendering, you can continue by other window!
void OGL3_Renderer::New_Frame() {
	/*
	if (Keyboard_Controller::Is_Key_Pressed(KEYBOARD_C)) {
		cout << "Key is pressed and shaders are compiling!\n";
		OGL3_Shader::Compile_All_Shaders();
	}
	//Run each scene, this means run every scene's gameplay codes! These will probably update the render contexts, so run RenderGraphs later!
	for (Scene* SCENE : Scene::ALL_SCENEs) {
		SCENE->Run_Scene();
	}
	cout << "Runned the scenes!\n";
	//Run each scene's RenderGraph, but in final production: Only run the displaying scene's RenderGraph!
	for (Scene* SCENE : Scene::ALL_SCENEs) {
		GFX_RenderGraph* RenderGraph = (GFX_RenderGraph*)SCENE->Return_RenderGraph();
		RenderGraph->Run_RenderGraph();
	}
	*/
}


void OGL3_Renderer::Send_Quad_to_GPU() {
	vec2 quadVertices[] = {
		// positions   // texCoords
		vec2(-1.0f, 1.0f),
		vec2(-1.0f, -1.0f),
		vec2(1.0f, -1.0f),

		vec2(-1.0f, 1.0f),
		vec2(1.0f, -1.0f),
		vec2(1.0f, 1.0f),
	};

	vec2 quadTextCoords[] = {
		vec2(0.0f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f)
	};

	//Load once!
	unsigned int position_buffer_size = 6 * sizeof(vec2);
	GLuint PostProcessQuad_VAO, PostProcessQuad_VBO;
	glGenVertexArrays(1, &PostProcessQuad_VAO);
	glGenBuffers(1, &PostProcessQuad_VBO);
	glBindVertexArray(PostProcessQuad_VAO);
	GFX_API::GFX_API_OBJ->Check_GL_Errors("Error after binding VAO");

	glBindBuffer(GL_ARRAY_BUFFER, PostProcessQuad_VBO);
	glBufferData(GL_ARRAY_BUFFER, position_buffer_size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_buffer_size, quadVertices);
	glBufferSubData(GL_ARRAY_BUFFER, position_buffer_size, position_buffer_size, quadTextCoords);
	GFX_API::GFX_API_OBJ->Check_GL_Errors("Error after glBufferSubDatas");


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)(position_buffer_size));
	GFX_API::GFX_API_OBJ->Check_GL_Errors("Error after attribute settings");

	glBindVertexArray(0);
	cout << "Quad Mesh VAO: " << PostProcessQuad_VAO << endl;
	//GFXI_MESH* gpu_mesh = new GFXI_MESH;
	//gpu_mesh->Indices_Number = 6;
	//gpu_mesh->VAO = PostProcessQuad_VAO;
	//gpu_mesh->VBO = PostProcessQuad_VBO;
}

void OGL3_Renderer::Show_RenderTarget_onWindow(GFX_WINDOW* WINDOW_to_Display, GFX_Render_Target* RenderTarget_to_Show) {
	//Bind Main Window Context and set other states!
	GFX_API::GFX_API_OBJ->Bind_Window_Context(WINDOW_to_Display);
	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	//Bind Material Instance to display Render Target and bind Render Texture!
	Material_Instance* PP_TextureDisplay_MatInst = TuranAPI::File_System::Material_Instance::Find_MaterialInstance_byName("PP_TextureDisplay_inst");
	PP_TextureDisplay_MatInst->Set_Uniform_Data("Display_Texture", &RenderTarget_to_Show->ID);
	//PP_TextureDisplay_MatInst->Set_Uniform_Data("Display_Texture", &TuranAPI::File_System::Texture_Resource::ALL_TEXTUREs[0]->GL_ID);
	Bind_Material_Instance(PP_TextureDisplay_MatInst);

	//Draw Full-Screen Quad!
	//Note: Quad Mesh's VAO is 1, so we will directly access it! If you want to check it, you can 
	glBindVertexArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


	//RENDERER FUNCTIONs

void OGL3_Renderer::Bind_Framebuffer(GFX_Framebuffer* FRAMEBUFFER) {
	if (FRAMEBUFFER) {
		glBindFramebuffer(GL_FRAMEBUFFER, FRAMEBUFFER->ID);
	}
}

void OGL3_Renderer::Change_Framebuffer_Resolution(GFX_Framebuffer* FRAMEBUFFER, unsigned int width, unsigned int height) {
	Bind_Framebuffer(FRAMEBUFFER);
	for (GFX_Render_Target* rt : FRAMEBUFFER->BOUND_RTs) {
		glBindTexture(GL_TEXTURE_2D, rt->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, Find_Texture_Format(rt->FORMAT), width, height, 0, Find_RenderTarget_Channel_Type(rt->FORMAT), Find_Texture_Value_Type(rt->FORMAT_VALUETYPE), NULL);
	}
	if (glGetError() != 0) {
		cout << "Error: When changing Framebuffer resolution!\n";
	}
	FRAMEBUFFER->WIDTH = width;
	FRAMEBUFFER->HEIGHT = height;
}

//Each Render Target Texture is in linear filter mode!
void OGL3_Renderer::Create_RenderTarget(GFX_Framebuffer* FRAMEBUFFER, unsigned int width, unsigned int height, TuranAPI::TuranAPI_ENUMs dimension, GFX_ENUM format, GFX_ENUM attachment, TuranAPI::TuranAPI_ENUMs value_type) {
	GFX_Render_Target* gfx_rt = new GFX_Render_Target;
	//Note: Wrapping isn't supported for Render Target Textures
	gfx_rt->ATTACHMENT = attachment;
	gfx_rt->DIMENSION = dimension;
	gfx_rt->FORMAT = format;
	gfx_rt->FORMAT_VALUETYPE = value_type;

	int ATTACHMENT_TYPE = Find_Texture_Attachment_Type(attachment);
	int CHANNEL_TYPE = Find_RenderTarget_Channel_Type(format);
	int FORMAT = Find_Texture_Format(format);
	int DIMENSION = Find_Texture_Dimension(dimension);
	int VALUE_TYPE = Find_Texture_Value_Type(value_type);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int rt_id;
	glGenTextures(1, &rt_id);
	glBindTexture(GL_TEXTURE_2D, rt_id);
	glTexImage2D(GL_TEXTURE_2D, 0, FORMAT, width, height, 0, CHANNEL_TYPE, VALUE_TYPE, NULL);
	cout << "Created RT ID:" << rt_id << endl;

	GFX_API::GFX_API_OBJ->Check_GL_Errors("When creating Render Target for Attachment: " + to_string(attachment) + "!");

	gfx_rt->ID = rt_id;
	FRAMEBUFFER->BOUND_RTs.push_back(gfx_rt);
}

//We recommend you to call Check_Framebuffer_Status() after this function!
void OGL3_Renderer::Attach_RenderTargets_to_Framebuffer(GFX_Framebuffer* FRAMEBUFFER) {
	Bind_Framebuffer(FRAMEBUFFER);
	for (GFX_Render_Target* rt : FRAMEBUFFER->BOUND_RTs) {
		glBindTexture(GL_TEXTURE_2D, rt->ID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, Find_Texture_Attachment_Type(rt->ATTACHMENT), GL_TEXTURE_2D, rt->ID, 0);
	}
}

//Argument "name_of_framebuffer" is only used to cout meaningful info, nothing functional!
void OGL3_Renderer::Check_ActiveFramebuffer_Status(string name_of_framebuffer) {
	int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE) {
		cout << "Draw Pass: " << name_of_framebuffer << "'s framebuffer is successfully created!\n";
		return;
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
		cout << "Error: Draw Pass: " << name_of_framebuffer << "'s framebuffer has incomplete attachment!\n";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
		cout << "Error: Draw Pass: " << name_of_framebuffer << "'s framebuffer has incomplete missing attachment!\n";
	}
	if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
		cout << "Error: Draw Pass: " << name_of_framebuffer << "'s framebuffer has unsupported type of attachment!\n";
	}
}

void OGL3_Renderer::Set_Depth_Test(GFX_ENUM DEPTH_TEST_MODE, GFX_ENUM DEPTH_BUFFER_MODE) {
	//Set Depth Func at start!
	glDepthFunc(Find_GFX_DepthTest_Mode(DEPTH_TEST_MODE));
	switch (DEPTH_BUFFER_MODE) {
	case GFX_DEPTH_OFF:
		cout << "Depth Test is closed!\n";
		glDisable(GL_DEPTH_TEST);
		return;
	case GFX_DEPTH_READ_ONLY:
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		return;
	case GFX_DEPTH_READ_WRITE:
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		return;
	default:
		cout << "Error: Intended Depth Buffer mode isn't supported!\n";
		return;
	}
}

GFX_Framebuffer* OGL3_Renderer::Create_Framebuffer(unsigned int width, unsigned int height) {
	GFX_Framebuffer* FRAMEBUFFER = new GFX_Framebuffer(width, height);
	glGenFramebuffers(1, &FRAMEBUFFER->ID);
	GFX_API::GFX_API_OBJ->Check_GL_Errors("After creating a Framebuffer!");
	return FRAMEBUFFER;
}

void OGL3_Renderer::Clear_RenderTarget(GFX_Framebuffer* FRAMEBUFFER, GFX_ENUM ATTACHMENT, vec3 CLEAR_COLOR) {
	if (Active_Framebuffer != FRAMEBUFFER) { Bind_Framebuffer(FRAMEBUFFER); }
	switch (ATTACHMENT) {
	case GFX_TEXTURE_COLOR0_ATTACHMENT:
		glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	case GFX_TEXTURE_DEPTH_ATTACHMENT:
		glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, 1);
		glClear(GL_DEPTH_BUFFER_BIT);
		return;
	default:
		cout << "Error: Clearing this Render Target attachment isn't supported for now!\n";
		cout << "Note: Don't forget, all of the COLOR BUFFER ATTACHMENTs are cleared when COLOR0_ATTACHMENT is cleared!\n";
		return;
	}
}

void OGL3_Renderer::Compile_MaterialType(string* compilation_status, const string* vertex_source, const string* fragment_source, unsigned int* program_id, unsigned int* vertex_id, unsigned int* fragment_id) {
	unsigned int vertexShader_o, fragmentShader_o, shaderProgram;
	//If we need to set argument ids in the end, we should set this true!
	bool set_ids = true;
	if (program_id == nullptr) {
		program_id = new unsigned int;
		vertex_id = new unsigned int;
		fragment_id = new unsigned int;
		vertexShader_o = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader_o = glCreateShader(GL_FRAGMENT_SHADER);
		shaderProgram = glCreateProgram();
	}
	//If shader isn't compiled before, create and compile a new one!
	else if (*program_id == 0 && *vertex_id == 0 && *fragment_id == 0) {
		vertexShader_o = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader_o = glCreateShader(GL_FRAGMENT_SHADER);
		shaderProgram = glCreateProgram();
		cout << "Created new shaders!\n";
	}
	//If shader is compiled before, bind them!
	else {
		vertexShader_o = *vertex_id;
		fragmentShader_o = *fragment_id;
		shaderProgram = *program_id;
		set_ids = false;
		return;
	}
	//Compile vertex shader and set ID!
	const char* vertex_source_cstr = vertex_source->c_str();
	glShaderSource(vertexShader_o, 1, &vertex_source_cstr, NULL);
	glCompileShader(vertexShader_o);

	//Check compile issues!
	int success;
	char vert_infolog[512];
	glGetShaderiv(vertexShader_o, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader_o, 512, NULL, vert_infolog);
		*compilation_status = "Error: Vertex Shader couldn't compile!\n" + (string)"\n Error Info: " + vert_infolog + "\n" + "Vertex Source:\n" + *vertex_source;
		TuranAPI::Breakpoint();
		return;
	}


	//Compile fragment shader and set ID!
	const char* fragment_source_cstr = fragment_source->c_str();
	glShaderSource(fragmentShader_o, 1, &fragment_source_cstr, NULL);
	glCompileShader(fragmentShader_o);

	//Check compile issues!
	int frag_success;
	char frag_infolog[512];
	glGetShaderiv(fragmentShader_o, GL_COMPILE_STATUS, &frag_success);
	if (!frag_success) {
		glGetShaderInfoLog(fragmentShader_o, 512, NULL, frag_infolog);
		*compilation_status = "Error: Fragment Shader couldn't compile!\n" + (string)"\n Error Info: " + frag_infolog + "\n" + "Fragment Source:\n" + *fragment_source;
		TuranAPI::Breakpoint();
		return;
	}


	//Link Vertex and Fragment Shader to Shader Program and set ID
	glAttachShader(shaderProgram, vertexShader_o);
	glAttachShader(shaderProgram, fragmentShader_o);
	glLinkProgram(shaderProgram);

	//Check linking issues
	int link_success;
	char link_infolog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_success);
	if (!link_success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, link_infolog);
		*compilation_status = "Error: Shader Program couldn't link!\n" + (string)link_infolog + "\n";
		TuranAPI::Breakpoint();
		return;
	}
	if (set_ids) {
		*program_id = shaderProgram;
		*vertex_id = vertexShader_o;
		*fragment_id = fragmentShader_o;
	}
}

void OGL3_Renderer::Send_Textures_to_GPU(vector<TuranAPI::File_System::Texture_Resource*>* Textures) {
	unsigned int i = 0;
	for (TuranAPI::File_System::Texture_Resource* texture : *Textures) {
		if (texture->GL_ID != 0) {
			continue;
		}

		int texture_D = Find_Texture_Dimension(texture->Properties.DIMENSION);
		int Channel_Type = Find_Texture_Channel_Type(texture->Properties.CHANNEL_TYPE);
		int Value_Type = Find_Texture_Value_Type(texture->Properties.VALUE_TYPE);
		int Wrapping = Find_Texture_Wrapping(texture->Properties.WRAPPING);
		int Mipmap_Filtering = Find_Texture_Mipmap_Filtering(texture->Properties.MIPMAP_FILTERING);
		//All texture should be upscaled linearly!
		int Upscale_filtering = GL_LINEAR;


		glGenTextures(1, &texture->GL_ID);
		GFX_API::GFX_API_OBJ->Check_GL_Errors("After generating the texture!\n");
		glBindTexture(texture_D, texture->GL_ID);
		GFX_API::GFX_API_OBJ->Check_GL_Errors("After binding the texture!\n");


		// Set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(texture_D, GL_TEXTURE_WRAP_S, Wrapping);
		glTexParameteri(texture_D, GL_TEXTURE_WRAP_T, Wrapping);
		glTexParameteri(texture_D, GL_TEXTURE_MIN_FILTER, Mipmap_Filtering);
		glTexParameteri(texture_D, GL_TEXTURE_MAG_FILTER, Upscale_filtering);
		GFX_API::GFX_API_OBJ->Check_GL_Errors("After setting Wrapping and Filtering!\n");
		cout << "Set wrapping!\n";
		glTexImage2D(texture_D, 0, Channel_Type, texture->WIDTH, texture->HEIGHT, 0, Channel_Type, Value_Type, texture->DATA);
		glGenerateMipmap(texture_D);
		//glGenerateMipmap(texture_D);
		GFX_API::GFX_API_OBJ->Check_GL_Errors("After sending model texture: " + to_string(i) + "!\n");
		cout << "TexImage2D is finished!\n";
		cout << "Texture's GL_ID is: " << texture->GL_ID << endl;
		i++;
	}
	cout << "Sent Texture Number: " << i << endl;
}

void OGL3_Renderer::Send_StaticModelDatas_to_GPU(vector<TuranAPI::File_System::Static_Model_Data*>* StaticModel_Datas) {
	unsigned int sent_mesh_number = 0;
	//For each model in scene!
	for (Static_Model_Data* model_data : *StaticModel_Datas) {
		//Send each mesh part of the model to GPU!
		//Note: Each mesh has a different material according to .obj
		for (unsigned int mesh_index_in_model = 0; mesh_index_in_model < model_data->Get_Mesh_Number(); mesh_index_in_model++) {
			Static_Mesh_Data* mesh_data = model_data->Get_Mesh_byIndex(mesh_index_in_model);

			//If mesh is sent to GPU before, skip!
			if (mesh_data->GFXI_MESH != nullptr) {
				continue;
			}

			//Calculate the buffer size for the mesh!
			unsigned int Indices_Size = mesh_data->Get_Indice_Number() * sizeof(unsigned int);

			unsigned int Positions_Size = mesh_data->Get_Vertex_Number() * sizeof(vec3);
			unsigned int TextCoords_Size = mesh_data->Get_Vertex_Number() * sizeof(vec2);
			//Note: These have the same size with Positions_Size but I did this to understand the code better and debug easier!
			unsigned int Normals_Size = mesh_data->Get_Vertex_Number() * sizeof(vec3);
			unsigned int Tangents_Size = mesh_data->Get_Vertex_Number() * sizeof(vec3);
			unsigned int Bitangents_Size = mesh_data->Get_Vertex_Number() * sizeof(vec3);
			unsigned int Total_Vertex_Data_Size = Positions_Size + TextCoords_Size + Normals_Size + Tangents_Size + Bitangents_Size;

			GFXI_MESH* gfx_mesh = new GFXI_MESH;
			glGenVertexArrays(1, &gfx_mesh->VAO);
			glGenBuffers(1, &gfx_mesh->VBO);
			glGenBuffers(1, &gfx_mesh->EBO);
			gfx_mesh->Indices_Number = mesh_data->Get_Indice_Number();
			gfx_mesh->Vertex_Number = mesh_data->Get_Vertex_Number();

			glBindVertexArray(gfx_mesh->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, gfx_mesh->VBO);
			glBufferData(GL_ARRAY_BUFFER, Total_Vertex_Data_Size, NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, NULL, Positions_Size, mesh_data->Get_Positions());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size, TextCoords_Size, mesh_data->Get_TextCoords());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size + TextCoords_Size, Normals_Size, mesh_data->Get_Normals());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size + TextCoords_Size + Normals_Size, Tangents_Size, mesh_data->Get_Tangents());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size + TextCoords_Size + Normals_Size + Tangents_Size, Bitangents_Size, mesh_data->Get_Bitangents());


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx_mesh->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices_Size, mesh_data->Get_Indices(), GL_STATIC_DRAW);

			//Position Attribute
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
			//TextCoord Attribute
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)Positions_Size);
			//Vertex Normal Attribute
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(Positions_Size + TextCoords_Size));
			//Tangent Attribute
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(Positions_Size + TextCoords_Size + Normals_Size));
			//Bitangent Attribute
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(Positions_Size + TextCoords_Size + Normals_Size + Tangents_Size));


			cout << "GPU Mesh Buffer is sent for Mesh: " << model_data->NAME << endl;
			mesh_data->Set_GFXI_Mesh(gfx_mesh);
			mesh_data->GFXI_MESH = gfx_mesh;
			sent_mesh_number++;
		}
	}
	cout << "Mesh number that is sent to GPU: " << sent_mesh_number << endl;
}

void Bind_Uniform(const unsigned int& PROGRAM_ID, const Material_Uniform* uniform);

void OGL3_Renderer::Bind_Material_Instance(TuranAPI::File_System::Material_Instance* MATERIAL_INST) {
	if (MATERIAL_INST->Material_Type->GFX_API != TuranAPI::OPENGL3) {
		cout << "Error: Bound Material Instance's Type isn't written in OpenGL3!\n";
		SLEEP_THREAD(10);
		return;
	}

	GFX_API::GFX_API_OBJ->Check_GL_Errors("Before binding shader!\n");
	unsigned int PROGRAM_ID = MATERIAL_INST->Material_Type->PROGRAM_ID;
	if (Active_ShaderProgram != MATERIAL_INST->Material_Type) { glUseProgram(PROGRAM_ID); }		//Bind Material Type (Shader Program), if it's not active!

	//Bind each uniform!
	for (Material_Uniform UNIFORM : MATERIAL_INST->UNIFORM_LIST) {
		Bind_Uniform(PROGRAM_ID, &UNIFORM);
	}
}

void OGL3_Renderer::Draw_Indexed_Objects(vector<void*> Vertex_Attributes, vector<unsigned int> Indice_Numbers) {
	for (unsigned int i = 0; i < Vertex_Attributes.size(); i++) {
		void* Attrib = Vertex_Attributes[i];
		unsigned int Indice_Number = Indice_Numbers[i];
		glBindVertexArray(*(unsigned int*)Attrib);
		glDrawElements(GL_TRIANGLES, Indice_Number, GL_UNSIGNED_INT, 0);
		GFX_API::GFX_API_OBJ->Check_GL_Errors("After drawing a mesh in G-Buffer Draw Pass!");
	}
}













void Bind_Uniform(const unsigned int& PROGRAM_ID, const Material_Uniform* uniform) {
	//Get Uniform Location!
	int location = glGetUniformLocation(PROGRAM_ID, uniform->VARIABLE_NAME.c_str());
	if (location == -1) {
		cout << "Error: Intended uniform: " << uniform->VARIABLE_NAME << " can't be found by OGL3_Material::Send_Uniform!\n";
		SLEEP_THREAD(10);
		return;
	}
	if (uniform->DATA == nullptr) {
		cout << "Error: Uniform: " << uniform->VARIABLE_NAME << " data isn't set!\n";
		SLEEP_THREAD(10);
		return;
	}

	void* data = uniform->DATA;
	switch (uniform->VARIABLE_TYPE) {
	case TuranAPI::VAR_UINT32:
		glUniform1i(location, *(unsigned int*)data);
		break;
	case TuranAPI::VAR_INT32:
		glUniform1i(location, *(int*)data);
		break;
	case TuranAPI::VAR_FLOAT32:
		glUniform1f(location, *(float*)data);
		break;
	case TuranAPI::VAR_VEC2:
		glUniform2f(location, ((vec2*)data)->x, ((vec2*)data)->y);
		break;
	case TuranAPI::VAR_VEC3:
		glUniform3f(location, ((vec3*)data)->x, ((vec3*)data)->y, ((vec3*)uniform->DATA)->z);
		break;
	case TuranAPI::VAR_VEC4:
		glUniform4f(location, ((vec4*)data)->x, ((vec4*)data)->y, ((vec4*)uniform->DATA)->z, ((vec4*)uniform->DATA)->w);
		break;
	case TuranAPI::VAR_MAT4x4:
		glUniformMatrix4fv(location, 1, GL_FALSE, (float*)data);
		break;
	case TuranAPI::API_TEXTURE_2D:
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *(unsigned int*)uniform->DATA);
		break;
	default:
		cout << "Error: Sending an unsupported uniform type! Nothing happened!\n";
		SLEEP_THREAD(10);
		return;
	}
}