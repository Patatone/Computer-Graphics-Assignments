// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past Assignment13 code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>

#include <algorithm>
#include <cstdint>
#include <limits>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

// A13: Queue family struct
struct QueueFamilyIndices {
	//std:optional used to be cuse that at least one Family exists
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

// A14: Device extensions list
const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
// A14: Swap chain support struct
struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Assignment14 {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	// place all the application variables here. As an example, here the one for the GLFW Window
	// and the Vulkan instances are already defined.

	GLFWwindow* window;
	VkInstance instance;

	// Presentation surface handle 
	VkSurfaceKHR surface;
	// Selected graphics card
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	// Store the logical device handle in
	VkDevice device;
	// Graphics queue handle
	VkQueue graphicsQueue;
	// Present queue handle
	VkQueue presentQueue;
	// Command pool - memory manager for command buffers
	VkCommandPool commandPool;
	// Command buffer object (destroyed with command pool)
	VkCommandBuffer commandBuffer;

	// A14
	// Swap chain object
	VkSwapchainKHR swapChain;
	// Swap chain image handles
	std::vector<VkImage> swapChainImages;
	// Swap chain image format
	VkFormat swapChainImageFormat;
	// Swap chain extent
	VkExtent2D swapChainExtent;

	std::vector<VkImageView> swapChainImageViews; // Image Views

	void initWindow() {
		// init GLFW library
		glfwInit();

		// do not create an OpenGL context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// disable window resizing
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		// create window
		window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 14", nullptr, nullptr);
	}

	void initVulkan() {
		// connection between application and Vulkan library
		createInstance();

		// Continue with:
		// Prsentation Surface Creation
		createSurface();
		// Physical Device selection
		pickPhysicalDevice();
		// Logical Device creation
		createLogicalDevice();
		// Command Pool creation
		createCommandPool();
		// Command Buffer creation
		createCommandBuffer();

		//****** New!
		// Swap chain creation
		createSwapChain();

		// Image view creation
		createImageViews();
	}

	void createSurface() {
		// Create the presentation surface
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	/* A13: Find availiable queue families with support for needed commands*/
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		// Queues are grouped into families, each one supporting different type of operations they can execute
		// Retrieve the number of queue families
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		// Allocate vector to store queue families
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		// See if one of the queue families supports VK_QUEUE_GRAPHICS_BIT
		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}
			// Look for queue family that can present to our window surface
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			// Check if supported and store presentation family queue index
			if (presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}
			i++;
		}

		return indices;
	}

	// Sevice suitability checks
	// Ensure that the device can process the commands we want to use
	bool isDeviceSuitable(VkPhysicalDevice device) {
		// "findQueueFamilies()" looks for all the queue families we need
		QueueFamilyIndices indices = findQueueFamilies(device);

		// A14: Check for device extension support
		bool extensionsSupported = checkDeviceExtensionSupport(device);

		// A14: Check for adequate swap chain support
		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}


	/* A14: Check for device extension support */
	bool checkDeviceExtensionSupport(VkPhysicalDevice device) {

		// Enumerate extensions and check if the required extensions are among them
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}
		return requiredExtensions.empty();
	}

	void pickPhysicalDevice() {
		// Listing the graphics cards
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}
		// Allocate an array to hold all of the VkPhysicalDevice handles
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		// If a device is compatible with requirements set it to "physicalDevice" variable 
		for (const auto& device : devices) {
			if (isDeviceSuitable(device)) {
				physicalDevice = device;
				break;
			}
		}

		if (physicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("failed to find a suitable GPU!");
		}

	}

	void createLogicalDevice() {
		// Find queue families
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		// Struct for creating queues for all unique families
		// Assign priorities to queues
		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			// Specify VkDeviceQueueCreateInfo
			// It describes the number of queues we want for a single queue
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			// For each queue set the family index and the count
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		// Specify is the set of device features that we'll be using
		VkPhysicalDeviceFeatures deviceFeatures{};

		// Device info structure
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		// A14: Enable extensions
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		// Instantiate logical device
		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}
		// Retrieve queue handles for each queue family
		vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
	}

	// Group of Command Buffers
	void createCommandPool() {
		QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create command pool!");
		}
	}

	// Each queue may handle several command buffers, to allow different threads running
	// on separate cores recording commands in parallel
	void createCommandBuffer() {
		// Struct to specify command pool and number of buffers to allocate
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	/* A14: Create a swap chain */
	// Screen Synchronization is handled with a generic circular queue, called the Swap Chain.
	// The swap chain is essentially a queue of images that are waiting to be presented to the screen.
	// 
	// Each swap chain is characterized by:
	// - A set of capabilities
	// - Several supported formats
	// - Several presentation modes
	void createSwapChain() {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);
		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
		// Number of images in swap chain (min +1)
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		// Do not extend max (no max)
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}
		// Struct for Swap chain details
		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		// Swap chain images details
		// Number of images in the buffers
		createInfo.minImageCount = imageCount;
		// Format of images in the buffers
		createInfo.imageFormat = surfaceFormat.format;
		// The color space
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		// Number of layers used
		createInfo.imageArrayLayers = 1;
		// Swap chain images will be used for rendering
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		// Get queue families
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		// How to handle swap chain images across multiple queue families
		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}
		// Dont apply any transform
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		// What should be done with the alpha channel
		// Ignore alpha channel
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		// Do not care about color of obscured pixels
		createInfo.clipped = VK_TRUE;
		// Possible reference to old swap chain
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		// Create swap chain
		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}
		// Retrieve swap chain image handles
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr); // Find final number of images
		swapChainImages.resize(imageCount); // Resize array to hold images
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
		// Store format and extent of swap chain
		swapChainImageFormat = surfaceFormat.format;
		swapChainExtent = extent;
	}
	/* A14: Help function to query for swap chain support */
	// Each swap chain is characterized by:
	// - A set of capabilities
	// - Several supported formats
	// - Several presentation modes
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {

		SwapChainSupportDetails details;
		// Get surface capabilities for physical device
		// Is include the size of the framebuffer, and the
		// minimumand maximum number of buffers supported
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		// Get supported surface formats
		// Even if colors are encoded using the RGB system, several
		// alternative formats, with different color spacesand resolution exist.
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		// Get supported presentation modes 
		// They are synchronization the algorithms in Vulkan terminology
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}
		return details;
	}
	/* A14: Help function for choosing swap surface format */
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {

		// Look for preferred combination of format and color space
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}
		// If not found use the first one
		return availableFormats[0];
	}
	/* A14: Help function for choosing swap present mode */
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {

		// Look for prefered present mode
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}
		// If not found use energy saving mode
		return VK_PRESENT_MODE_FIFO_KHR;
	}
	/* A14: Help function to choose swap extent (resolution of swap chain images) */
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {

		// Pick resolution that best matches window size
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}
		else {
			// Get pixel resolution
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};
			// Compare pixel resolution to actual image resolution
			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
			return actualExtent;
		}
	}

	/* A14: Create image views */
	// It describes how to access the image and which part of the image to access
	void createImageViews() {
		// Resize the list to fit all of the image views we will create
		swapChainImageViews.resize(swapChainImages.size());

		// Iterate over all swap chain images
		for (size_t i = 0; i < swapChainImages.size(); i++) {

			// Struct to specify parameters for image view
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

			// Corresponding image itself - most important info
			createInfo.image = swapChainImages[i];

			// How to interpret image data
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = swapChainImageFormat;

			// Color mapping
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			// Image purpose, parts of image to access: color targets without mipmapping levels or multiple layers
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;
			// Create image view
			if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create image views!");
			}
		}
	}

	void createInstance() {

		// Struct with info about application
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Assignment 14";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Struct with info for creating an instance
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// Find needed extension(s) to interface with the window system
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		// Pass it to the struct
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		// Enable global validation layers (later)
		createInfo.enabledLayerCount = 0;

		// Create instance
		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		// Check if instance creation was successful
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void mainLoop() {
		// Wait for the window to close
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	/* Deallocate resources*/
	void cleanup() {
		// A13: destroy command pool
		vkDestroyCommandPool(device, commandPool, nullptr);
		// A13: destroy logical device
		vkDestroyDevice(device, nullptr);

		// A14: Destroy all swap chain image views
		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(device, imageView, nullptr);
		}
		// A14: destroy swap chain
		vkDestroySwapchainKHR(device, swapChain, nullptr);

		// A13: destroy presentation surface
		vkDestroySurfaceKHR(instance, surface, nullptr);

		// destroy instance
		vkDestroyInstance(instance, nullptr);
		// destroy window
		glfwDestroyWindow(window);
		// terminate GLFW
		glfwTerminate();
	}
};

int main() {
	Assignment14 app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}