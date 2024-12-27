#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

struct PointLight{
	vec3 position;

	// attenuation variables
	float constant;
	float linear;
	float quadratic;

	// light variables
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform PointLight pointLight;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
	PointLight pointLight;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;

void main() {
	mat3 normalMatrix = transpose(inverse(mat3(view * model)));

	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vs_out.FragPos = vec3(view * model * vec4(aPos, 1.0));
	vs_out.Normal = normalMatrix * aNormal;
	vs_out.TexCoords = aTexCoords;

	vs_out.pointLight = pointLight;
	vs_out.pointLight.position = vec3(view * vec4(pointLight.position, 1.0));
}