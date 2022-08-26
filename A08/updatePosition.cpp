// Initial position, given by the text
static glm::vec3 pos = glm::vec3(-3, 0, 2);

float pitch = 0;

float rad_180 = glm::radians(180.0f);
float rad_90 = glm::radians(90.0f);
float rad_0 = 0.0f;

const float MOVE_SPEED = 1.5f;
glm::vec3 xAxis = glm::vec3(1, 0, 0);
glm::vec3 yAxis = glm::vec3(0, 1, 0);
glm::vec3 zAxis = glm::vec3(0, 0, 1);

// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {

	static auto startTime = std::chrono::high_resolution_clock::now();
	static float lastTime = 0.0f;
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>
		(currentTime - startTime).count();
	float deltaT = time - lastTime;
	lastTime = time;

	if (glfwGetKey(window, GLFW_KEY_A)) {
		//NewPos = OldPos - speed*time (needed to consider the function call time)
		pos -= MOVE_SPEED * xAxis * deltaT;
		pitch = rad_180;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		pos += MOVE_SPEED * xAxis * deltaT;
		pitch = rad_0;
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		pos -= MOVE_SPEED * zAxis * deltaT;
		pitch = rad_90;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		pos += MOVE_SPEED * zAxis * deltaT;
		pitch = -rad_90;
	}

	printf("Last function call: %f seconds ago.\n", deltaT);
	glm::mat4 T = glm::translate(glm::mat4(1), pos);
	//Rotation of the object
	glm::mat4 R_y = glm::rotate(glm::mat4(1), pitch, yAxis);
	return T * R_y;
}

