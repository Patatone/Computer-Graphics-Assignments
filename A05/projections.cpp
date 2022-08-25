float n = 0.1; //Near plane distance
float f = 9.9; //Far plane distance

// -> Create a matrix for Perspecrtive projection with the given aspect ratio a,
// -> and a FovY = 90o
glm::mat4 PO1(float a) {
	glm::mat4 Mlglm = glm::perspective(glm::radians(90.f), a, n, f);
	// Change the axis convention from OpenGL to Vulkan
	Mlglm[1][1] *= -1;
	return Mlglm;
}


// -> Create a matrix for Perspecrtive projection with the given aspect ratio a,
// -> and a FovY = 120o
glm::mat4 PO2(float a) {
	glm::mat4 Mlglm = glm::perspective(glm::radians(120.f), a, n, f);
	// Change the axis convention from OpenGL to Vulkan
	Mlglm[1][1] *= -1;
	return Mlglm;
}

// -> Create a matrix for Perspecrtive projection with the given aspect ratio a,
// -> and a FovY = 30o
glm::mat4 PO3(float a) {
	glm::mat4 Mlglm = glm::perspective(glm::radians(30.f), a, n, f);
	// Change the axis convention from OpenGL to Vulkan
	Mlglm[1][1] *= -1;
	return Mlglm;
}

// -> Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// -> Here the perspective should only show the left side of the view
// -> with a FovY = 90o. Here r=0, and l, t and b should be computed
// -> to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
	float tan_v = tan(glm::radians(90.f) / 2);

	float l = -a * n * tan_v;
	float b = -n * tan_v;
	float t = n * tan_v;
	float r = 0.0;

	//frustum() allows to compute the prospective projection matrix specifying the boundaries
	//First term of the product (scale()) flips the y-axis to match the Vulkan conventions.
	glm::mat4 Mlglm = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::frustum(l, r, b, t, n, f);
	return Mlglm;
}

