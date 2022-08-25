// MT1
// -> Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). 
// -> The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, 
// -> and then -60 degrees around the y-axis.

glm::mat4 T1 = glm::translate(glm::mat4(1), glm::vec3(1, 0, -1));
// Rotation 45 degrees around the x-axis
glm::mat4 RX1 = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(1, 0, 0));
// Rotation 30 degrees around the z-axis
glm::mat4 RZ1 = glm::rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 0, 1));
// Rotation -60 degrees around the y-axis
glm::mat4 RY1 = glm::rotate(glm::mat4(1), glm::radians(-60.0f), glm::vec3(0, 1, 0));
// Inverse order because we are using the matrix-on-the-left convention
glm::mat4 MT1 = T1 * RY1 * RZ1 * RX1 * glm::inverse(RZ1) * glm::inverse(RY1) * glm::inverse(T1);



// MT2
// -> Half the size of an object, using as fixed point (5,0,-2)

glm::mat4 T2 = glm::translate(glm::mat4(1), glm::vec3(5, 0, -2));
glm::mat4 S2 = glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, .5));
glm::mat4 MT2 = T2 * S2 * glm::inverse(T2);



// MT3
// -> Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane

glm::mat4 T3 = glm::translate(glm::mat4(1), glm::vec3(1, 1, 1));
// Scaling - mirroring with s=(1,-1,1) (negative value on the plane missing component, in this case y)
glm::mat4 S3 = glm::scale(glm::mat4(1), glm::vec3(1, -1, 1));
glm::mat4 RX3 = glm::rotate(glm::mat4(1), glm::radians(15.0f), glm::vec3(1, 0, 0));
glm::mat4 MT3 = T3 * RX3 * S3 * glm::inverse(RX3) * glm::inverse(T3);



// MT4
// -> Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5) then rotation of 30 degree around the Y axis, 
// -> and finally a uniform scaling of a factor of 3.

// Uniform scaling of a factor of 3
glm::mat4 S4 = glm::scale(glm::mat4(1), glm::vec3(3, 3, 3));
// Rotation of 30 degree around the Y axis
glm::mat4 RY4 = glm::rotate(glm::mat4(1), glm::radians(30.0f), glm::vec3(0, 1, 0));
// Translation of (0, 0, 5)
glm::mat4 T4 = glm::translate(glm::mat4(1), glm::vec3(0, 0, 5));
glm::mat4 MT4 = inverse(S4 * RY4 * T4);