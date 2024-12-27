#version 460 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColour;

struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 lightColour = vec3(0.0, 0.0, 0.7);

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir, float shininess);

void main() {
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(-FragPos);

	float shininess = 3.0;

	DirLight light = {
		vec3(0.0, 0.0, -1.0),
		vec3(0.2, 0.2, 0.2),
		vec3(0.5, 0.5, 0.5),
		vec3(1.0, 1.0, 1.0)
	};

	vec3 result = calculateDirLight(light, normal, viewDir, shininess);

	FragColour = vec4(result, 1.0);
}

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir, float shininess) {
	vec3 lightDir = normalize(-light.direction);

	// diffuse
	float diffuse = max(dot(normal, lightDir), 0.0);
	vec3 diffuseColour = light.diffuse * diffuse * lightColour;

	// specular
	float specular = 0.0;
	float specularStrength = 0.5;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	specular = pow(max(dot(normal, halfwayDir), 0.0), shininess);

	// resulting light
	vec3 specularColour = specularStrength * specular * lightColour;

	return (light.ambient * lightColour + diffuseColour + specularColour);
}