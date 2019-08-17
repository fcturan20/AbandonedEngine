#include "OGL3_Renderer_Core.h"


void OGL3_Renderer::Start_Creation() {
	//Compile all shader at Creation() because we don't want to get OpenGL initialization errors
	OGL3_Shader::Compile_All_Shaders();
	cout << "Compiled all shaders!\n\n";
	OGL3_Texture::Send_Textures_to_GPU();
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
	Check_OpenGL_Errors("Error after binding VAO");

	glBindBuffer(GL_ARRAY_BUFFER, PostProcessQuad_VBO);
	glBufferData(GL_ARRAY_BUFFER, position_buffer_size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_buffer_size, quadVertices);
	glBufferSubData(GL_ARRAY_BUFFER, position_buffer_size, position_buffer_size, quadTextCoords);
	Check_OpenGL_Errors("Error after glBufferSubDatas");


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)(position_buffer_size));
	Check_OpenGL_Errors("Error after attribute settings");

	glBindVertexArray(0);
	GFXI_MESH* gpu_mesh = new GFXI_MESH;
	//gpu_mesh->Indices_Number = 6;
	//gpu_mesh->VAO = PostProcessQuad_VAO;
	//gpu_mesh->VBO = PostProcessQuad_VBO;
	cout << "Quad Mesh VAO: " << PostProcessQuad_VAO << endl;
}