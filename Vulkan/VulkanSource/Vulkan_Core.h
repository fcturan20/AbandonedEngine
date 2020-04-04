#pragma once
#include "Vulkan_ENUMs.h"
#include "GFXSource/GFX_Core.h"

#include "Renderer/Vulkan_Resource.h"
#include "Renderer/Vulkan_Renderer_Core.h"
#include "Vulkan_FileSystem.h"

//RenderGraph will have specify which features it needs, so initialize Vulkan as little requirements as possible with as much info about system as possible.
//When application that uses this DLL, Application Developer should define a RenderGraph to do some Rendering.
//While specifying, he will specify features and we will test them later in somewhere (Maybe Bind_RenderGraph is good place for this)
namespace Engine{}
namespace Vulkan {
	class VK_API Vulkan_Core : public GFX_API::GFX_Core {
	public:
		Vulkan_Core();
		Vulkan_States VK_States;
		VkPipelineLayout FirstTriangle_PipelineLayout;
		VkRenderPass FirstTriangle_RenderPass;
		VkPipeline FirstTriangle_GraphicsPipeline = VK_NULL_HANDLE;
		ShaderPipeline* FirstTriangle_ShaderPipeline = nullptr;
		VkCommandPool FirstTriangle_CommandPool = {};
		Vector<VkCommandBuffer> FirstTriangle_CommandBuffers;


		virtual void Initialization() override;
		virtual void Check_Computer_Specs() override;
		virtual void Save_Monitors() override;
		virtual void Create_Renderer() override;

		//Window Operations
		virtual void Create_Window(const char* name) override;
		virtual void Close_Window(GFX_API::WINDOW* window) override;
		virtual void Change_Window_Resolution(GFX_API::WINDOW* window, unsigned int width, unsigned int height) override;
		virtual void Set_Window_Focus(GFX_API::WINDOW* window, bool is_focused) override;
		virtual void Bind_Window_Context(GFX_API::WINDOW* window) override;

		//Callbacks

		//Renderer Operations
		virtual void Render_IMGUI() override;
		virtual void Load_GFX_Files() override;

		//Input (Keyboard-Controller) Operations
		virtual void Take_Inputs() override;

		//Resource Destroy Operations
		virtual void Destroy_GFX_Resources() override;


		static void GFX_Error_Callback(int error_code, const char* description);

		//Validation Layers are actived if TURAN_DEBUGGING is defined
		void Create_Instance();
		//Initialization calls this function if TURAN_DEBUGGING is defined
		void Setup_Debugging();
		void Create_Surface_forWindow(WINDOW* vulkan_window);
		//A Graphics Queue is created for learning purpose
		void Setup_LogicalDevice();
		void Create_SwapChain_forWindow(WINDOW* vulkan_window);
		void Create_RenderPass();
		//I want to render first triangle, so create here
		void Create_GraphicsPipeline();
		//This function compiles SPIR-V from GLSL and instead of storing SPIR-V, uses SPIR-V to create a Shader Module
		void Create_ShaderPipeline(ShaderPipeline* Pipeline_to_Create, TuranAPI::File_System::Material_Type_Resource* MaterialType_to_Use);
		void Create_Framebuffers(WINDOW* vulkan_window);
		void Create_CommandPool();
		void Create_CommandBuffers();
		void Begin_RenderPass();
		void Begin_DrawingFirstTriangle();
		void Finish_DrawingProgresses();

	};

	VK_API GFX_API::GFX_Core* Start_VulkanSystems(TuranAPI::TAPI_Systems* TAPISystems);
}