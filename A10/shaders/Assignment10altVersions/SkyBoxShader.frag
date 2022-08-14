#version 450

layout(location = 0) in vec3 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform samplerCube skybox;

void main() {
	outColor = vec4(vec3(1.0,1.0,1.0) - texture(skybox, fragTexCoord).rgb, 1.0);
}