#version 450#extension GL_ARB_separate_shader_objects : enablelayout(location = 0) in vec3 fragPos;layout(location = 1) in vec3 fragNorm;layout(location = 2) in vec2 fragTexCoord;layout(location = 0) out vec4 outColor;layout(binding = 1) uniform sampler2D texSampler;layout(binding = 2) uniform GlobalUniformBufferObject {	// Direction of light (spot, directional)	vec3 lightDir;	// Position of light (spot, point)	vec3 lightPos;	// Basic color of light	vec3 lightColor;	vec3 eyePos;	// spot: .x = cos of outer angle, .y = cos of inner angle, 	// .z = basic distance g (spot, point), .w = denominator beta (spot, point)	vec4 coneInOutDecayExp;	vec4 selector;} gubo;/**** Modify from here *****///DIRECT LIGHT// Light sources very far away from the object =>// Uniformily influence the scene.// Because of the distance we consider ray parallel and constant in color and intensity.vec3 direct_light_dir(vec3 pos) {	// Directional light direction	return gubo.lightDir; }vec3 direct_light_color(vec3 pos) {	// Directional light color	return gubo.lightColor;}// POINT LIGHT// Light emitted from fixed point that emits light in all direction starting from a position.// The direction is a vector from object position to light position.vec3 point_light_dir(vec3 pos) {	// Point light direction	// Normalization of the distance between the light source and the object	return normalize(gubo.lightPos - pos);}vec3 point_light_color(vec3 pos) {	// Point light color        // Decay factor    float beta = gubo.coneInOutDecayExp.w;    // Distance at which light reduction is 1    // intensity higher than l for distance < g and will decrese for longer distances    float g = gubo.coneInOutDecayExp.z;    vec3 l = gubo.lightColor;    	return l * pow(g/length(gubo.lightPos - pos) ,beta);}// SPOT LIGHT// Conic source with a direction and a position// Two cone charaterized by 2 angles alpha_in alpha_out with differet intensityvec3 spot_light_dir(vec3 pos) {	// Spot light direction	return normalize(gubo.lightPos - pos);}vec3 spot_light_color(vec3 pos) {	// Spot light color    vec3 l = gubo.lightColor;    vec3 d = gubo.lightDir;    vec3 lx = normalize(gubo.lightPos - pos);        // Cosin of alpha_in    float c_in = gubo.coneInOutDecayExp.y;    // Cosin of alpha_out    float c_out = gubo.coneInOutDecayExp.x;    // Cosin of angle between light direction lx and direction if the spot d    float c_alpha = dot(lx, d);        // DECAY    // Decay factor    float beta = gubo.coneInOutDecayExp.w;    // Distance at which light reduction is 1    // Intensity higher than l for distance < g and will decrese for longer distances    float g = gubo.coneInOutDecayExp.z;        float dimming = clamp((c_alpha - c_out)/(c_in - c_out), 0, 1);    float decay = pow(g/length(gubo.lightPos - pos), beta);	return l * decay * dimming;}/**** To from here *****/void main() {	vec3 Norm = normalize(fragNorm);	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);		vec3 lD;	// light direction from the light model	vec3 lC;	// light color and intensity from the light model		lD = direct_light_dir(fragPos) * gubo.selector.x +	     point_light_dir(fragPos)  * gubo.selector.y +	     spot_light_dir(fragPos)   * gubo.selector.z;	lC = direct_light_color(fragPos) * gubo.selector.x +	     point_light_color(fragPos)  * gubo.selector.y +	     spot_light_color(fragPos)   * gubo.selector.z;	vec3 Diffuse = (texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w)) * (max(dot(Norm, lD),0.0f) );	vec3 Specular = vec3(pow(max(dot(EyeDir, -reflect(lD, Norm)),0.0f), 64.0f));		outColor = vec4((Diffuse + Specular) * lC, 1.0f);	}