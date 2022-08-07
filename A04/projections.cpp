float w = 2.0; // Half width
float n = -4.0; // Near plane
float f = 12.0; // Far plane

// Returns the Parallel Projection Matrix with aspect ratio a
glm::mat4 PPM_Matrix(float a) {
	glm::mat4 PPM = glm::mat4(1.0);
	PPM[0][0] = 1 / w;
	PPM[1][1] = -a / w;
	PPM[2][2] = 1 / (n - f);
	PPM[3][2] = n / (n - f);

	return PPM;
}

// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a) {
	//Isometric projections are obtained by applying a rotation of ±45o
	//around the y - axis, followed by a rotation of ±35.26o around the
	//x - axis, before applying the parallel projection previously seen.

	//Rotation of 45.00° around the y-axis
	glm::mat4 R1Y = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0, 1, 0));
	//Rotation of 35.26° around the x-axis
	glm::mat4 R1X = glm::rotate(glm::mat4(1), glm::radians(35.26f), glm::vec3(1, 0, 0));
	return PPM_Matrix(a) * R1X * R1Y;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
	//Dimetric projections are obtained by applying a rotation of ±45o
	//around the y - axis, followed by an arbitrary rotation a around the
	//x - axis, before applying the basic parallel projection.

	//Rotation of 45.00° around the y-axis
	glm::mat4 R2Y = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0, 1, 0));
	//Arbitrary rotation around the x-axis (alpha = 45 degree)
	glm::mat4 R2X = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1, 0, 0));
	return PPM_Matrix(a) * R2X * R2Y;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
	//Trimetric projections are obtained by applying an arbitrary rotation
	//b around the y - axis, followed by an arbitrary rotation a around the
	//x - axis, before applying the parallel projection previously seen.

	//Arbitrary rotation around the x-axis (alpha = 45 degree)
	glm::mat4 R3Y = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0, 1, 0));
	//Arbitrary rotation around the x-axis (beta = 60 degree)
	glm::mat4 R3X = glm::rotate(glm::mat4(1), glm::radians(60.0f), glm::vec3(1, 0, 0));
	return PPM_Matrix(a) * R3X * R3Y;
}

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a) {
	// Oblique projections can be obtained by applying a shear
	// along the z - axis before the orthogonal projection.
	// it can be expressed considering the angle alpha of the
	// axis, and the corresponding reduction factor r.
	// In this case for Cabinet projection (alpha = 45 degree and r = 0.5)

	glm::mat4 shear = glm::mat4(1.0);
	shear[2][0] = -0.5 * cos(glm::radians(45.0f));
	shear[2][1] = -0.5 * sin(glm::radians(45.0f));
	return PPM_Matrix(a) * shear;
}

