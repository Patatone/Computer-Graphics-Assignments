// Create a world matrix using position, Euler angles, and size
// Euler angles are passed in YPR parameter:
// YPR.x : Yaw
// YPR.y : Pitch
// YPR.z : Roll
glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size) {
	glm::mat4 T1 = glm::translate(glm::mat4(1.0), pos);
	glm::mat4 RY1 = glm::rotate(glm::mat4(1.0), glm::radians(YPR.x), glm::vec3(0, 1, 0));
	glm::mat4 RX1 = glm::rotate(glm::mat4(1.0), glm::radians(YPR.y), glm::vec3(1, 0, 0));
	glm::mat4 RZ1 = glm::rotate(glm::mat4(1.0), glm::radians(YPR.z), glm::vec3(0, 0, 1));
	glm::mat4 S1 = glm::scale(glm::mat4(1.0), size);
	return T1*RY1*RX1*RZ1*S1;
}

// Create a world matrix using position, quaternion angles, and size
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size) {
	glm::mat4 T2 = glm::translate(glm::mat4(1.0), pos);
	glm::mat4 R2 = glm::mat4(rQ); // Rotation
	glm::mat4 S2 = glm::scale(glm::mat4(1.0), size);
	return T2*R2*S2;
}

