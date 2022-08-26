// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include <optional>
#include <set>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;


class Assignment13 {
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

	struct QueueFamilyIndices {
		//std:optional used to be cuse that at least one Family exists
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	void initWindow() {
		// init GLFW library
		glfwInit();

		// do not create an OpenGL context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// disable window resizing
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		// create window
		window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 13", nullptr, nullptr);
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
		return indices.isComplete();
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

	void createInstance() {
		// Function for printing extensions
		// printExtensions();

		// Struct with info about application
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Assignment 13";
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
	Assignment13 app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}