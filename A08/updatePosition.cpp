float roll = 0, pitch = 0, yaw = 0;

float rad_180 = glm::radians(180.0f);
float rad_90 = glm::radians(90.0f);
float rad_0 = 0.0f;

static auto startTime = std::chrono::high_resolution_clock::now();
static auto lastTime = std::chrono::high_resolution_clock::now();
static bool action;

float getLastCall() {
	float deltaT = std::chrono::duration<float, std::chrono::seconds::period>
		(startTime - lastTime).count();
	return deltaT;
}
void executedCall() {
	lastTime = std::chrono::high_resolution_clock::now();
	action = true;
}

// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	action = false;
	static glm::vec3 pos = glm::vec3(-3, 0, 2);	// variable to store robot position
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
												//
												// this variable is here just as an example!
												// it should replaced or combined with
												//  the ones you think necessary for the task

	if (glfwGetKey(window, GLFW_KEY_A)) {
		pos -= glm::vec3(0.02, 0, 0);
		pitch = rad_180;
		executedCall();
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		pos += glm::vec3(0.02, 0, 0);
		pitch = rad_0;
		executedCall();
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		pos -= glm::vec3(0, 0, 0.02);
		pitch = rad_90;
		executedCall();
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		pos += glm::vec3(0, 0, 0.02);
		pitch = -rad_90;
		executedCall();
	}

	if (action) {
		printf("Last function call: %f seconds ago.\n", getLastCall());
	}
	glm::mat4 T = glm::translate(glm::mat4(1), pos);
	//Rotation of the object
	glm::mat4 R_y = glm::rotate(glm::mat4(1), pitch, glm::vec3(0, 1, 0));
	return T * R_y ;
}

