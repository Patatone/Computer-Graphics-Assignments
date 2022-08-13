#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

// Must compute a time dependent color and return it 
// in the four component variable
void main() {
	// The first three of the four elements are respectively the 
	// red, green and blue components of the color, all in the 0-1 range.
	// The last element of the vector is the transparency, 
	// and should be always set to 1
	outColor = vec4(abs(cos(gubo.time)), abs(sin(gubo.time)), abs(sin(gubo.time)*cos(gubo.time)*2), 1.0f);
}