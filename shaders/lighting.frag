#version 460 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material material;

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

in VS_OUT {
	PointLight pointLight;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

out vec4 FragColour;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

float calculateDiffuse(vec3 normal, vec3 lightDir);
float calculateSpecular(vec3 lightDir, vec3 viewDir, float shininess);
float calculateAttenuation(float constant, float linear, float quadratic, float dist);

void main() {
	// properties
	vec3 normal = normalize(fs_in.Normal);
	vec3 viewDir = normalize(-fs_in.FragPos);
	vec3 result = vec3(0.0);

	result += calculatePointLight(fs_in.pointLight, normal, fs_in.FragPos, viewDir);
	
	vec3 emission = texture(material.emission, fs_in.TexCoords).rgb;
	if (emission.r > 0){
		result += emission;
	}

	FragColour = vec4(result, 1.0);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	// diffuse
	float diff = calculateDiffuse(normal, lightDir);

	// specular
	float spec = calculateSpecular(lightDir, viewDir, material.shininess);

	// attenuation
	float dist = length(light.position - fragPos);
	float attenuation = calculateAttenuation(light.constant, light.linear, light.quadratic, dist);

	// combine results
	vec3 ambient = light.ambient * texture(material.diffuse, fs_in.TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, fs_in.TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, fs_in.TexCoords).rgb;
	
	// attenuate values
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return max((ambient + diffuse + specular), vec3(0.0, 0.0, 0.0));
}

float calculateDiffuse(vec3 normal, vec3 lightDir) {
	return max(dot(normal, lightDir), 0.0);
}

float calculateSpecular(vec3 lightDir, vec3 viewDir, float shininess) {
	vec3 halfDir = normalize(lightDir + viewDir);
	return pow(max(dot(viewDir, halfDir), 0.0), shininess);
}

float calculateAttenuation(float constant, float linear, float quadratic, float dist) {
	return 1.0 / (constant + linear * dist + quadratic * dist * dist);
}