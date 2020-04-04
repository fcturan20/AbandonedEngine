#pragma once
#include "Vulkan_Includes.h"
#include "GFXSource/GFX_ENUMs.h"
#include "GFXSource/GFX_Display.h"

//Vulkan Libs
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#define VULKAN_DEBUGGING

namespace Vulkan {
	class VK_API GPU : public GFX_API::GPU {
	public:
		GPU();
		VkPhysicalDevice Physical_Device = {};
		VkPhysicalDeviceProperties Device_Properties = {};
		VkPhysicalDeviceFeatures Device_Features = {};
		Vector<VkQueueFamilyProperties> QueueFamilies;
		uint32_t Graphics_QueueFamily = {}, Compute_QueueFamily = {}, Transfer_QueueFamily = {}, Presentation_QueueFamilyIndex = {};
		Vector<VkDeviceQueueCreateInfo> QueueCreationInfos;
		VkDeviceCreateInfo Logical_Device_CreationInfo = {};
		VkDevice Logical_Device = {};
		Vector<VkQueue> Queues;
		Vector<VkExtensionProperties> Supported_DeviceExtensions;
		Vector<const char*>* Required_DeviceExtensionNames;

		VkSurfaceCapabilitiesKHR SurfaceCapabilities = {};
		Vector<VkSurfaceFormatKHR> SurfaceFormats;
		Vector<VkPresentModeKHR> PresentationModes;
	};

	//Window will be accessed from only Vulkan.dll, so the programmer may be aware what he can cause
	class VK_API WINDOW : public GFX_API::WINDOW {
	public:
		WINDOW(unsigned int width, unsigned int height, GFX_API::GFX_ENUM display_mode, GFX_API::MONITOR* display_monitor, unsigned int refresh_rate, const char* window_name, GFX_API::GFX_ENUM v_sync);
		VkSurfaceKHR Window_Surface = {};
		VkSwapchainCreateInfoKHR Window_SwapChainCreationInfo = {};
		VkSwapchainKHR Window_SwapChain = {};
		Vector<VkImage> SwapChain_Images;
		Vector<VkImageView> SwapChain_ImageViews;
		GLFWwindow* GLFW_WINDOW = {};
		Vector<VkFramebuffer> Swapchain_Framebuffers;
	};

	//Use this class to store Vulkan Global Variables (Such as VkInstance, VkApplicationInfo etc)
	class VK_API Vulkan_States {
		friend class Vulkan_Core;
		Vulkan_States();
	public:
		VkInstance Vulkan_Instance;
		VkApplicationInfo Application_Info;
		VkInstanceCreateInfo Instance_CreationInfo;
		Vector<VkExtensionProperties> Supported_InstanceExtensionList;
		Vector<const char*>* Required_InstanceExtensionNames;

		VkLayerProperties* Supported_LayerList;
		uint32_t Supported_LayerNumber;
		VkDebugUtilsMessengerEXT Debug_Messenger;

		const char* const* Get_Supported_LayerNames(const VkLayerProperties* list, uint32_t length);
		//CONVERT VENDOR ID TO VENDOR NAME
		const char* Convert_VendorID_toaString(uint32_t VendorID);

		//Required Extensions are defined here
		//Check if Required Extension Names are supported!
		//Returns true if all of the required extensions are supported!
		void Is_RequiredInstanceExtensions_Supported();
		//Same for Device
		void Is_RequiredDeviceExtensions_Supported(GPU* Vulkan_GPU);

		static VKAPI_ATTR VkBool32 VKAPI_CALL VK_DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT Message_Severity,
			VkDebugUtilsMessageTypeFlagsEXT Message_Type,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallback_Data,
			void* pUserData);


		PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT();
		PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT();
	};

}