#version 450
#extension GL_ARB_separate_shader_objects : enable

	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

	gl_Position = vec4(inPosition, 1.0);
	fragTexCoord = inTexCoord;
}