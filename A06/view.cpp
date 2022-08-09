 // Create a look in direction matrix
 // Pos    -> Position of the camera
 // Angs.x -> direction (alpha)
 // Angs.y -> elevation (beta)
 // Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {
	//Negative values because we are computing View Matrix, it's the inverse of the Camera Matrix.
	glm::mat4 RZ = glm::rotate(glm::mat4(1.0), -Angs.z, glm::vec3(0, 0, 1));
	//Inverted Angs.x and Angs.y rotation to fix the camera view
	glm::mat4 RY = glm::rotate(glm::mat4(1.0), -Angs.x, glm::vec3(0, 1, 0));
	glm::mat4 RX = glm::rotate(glm::mat4(1.0), -Angs.y, glm::vec3(1, 0, 0));
	glm::mat4 T = glm::translate(glm::mat4(1.0), -Pos);

	return RZ * RX * RY * T;
}

 // Create a look at matrix
 // Pos    -> Position of the camera (c)
 // aim    -> Posizion of the target (a)
 // Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	// Roll is not generally included in the Look-at view matrix model it's implemented
	// placing a rotation along the z-axis of -roll degree after transformation of the view matrix
	glm::mat4 ROLL = glm::rotate(glm::mat4(1), glm::radians(Roll), glm::vec3(0, 0, 1));
	// Up vector specified in the assignment text
	glm::mat4 VIEW = glm::lookAt(Pos, aim, glm::vec3(0, 1, 0));
	return ROLL * VIEW;
}



