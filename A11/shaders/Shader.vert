#version 450

// In this block it receives 3 matrices
layout(set = 0, binding = 0) uniform UniformBufferObject {
	mat4 worldMat;
	mat4 viewMat;
	mat4 prjMat;
} ubo;

// Position - the cartesian local coordinates of each vertex in variable
layout(location = 0) in vec3 inPosition;

void main() {
	// gl_Positionis is a vec4 variable that must be filled with the 
	// clipping coordinates of the vertex. Definition in the L08 slide.
	gl_Position = ubo.prjMat * ubo.viewMat * ubo.worldMat * vec4(inPosition, 1.0);
}