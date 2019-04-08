#version 330 core

in vec3 Normal;
in vec3 Position;
in vec3 LightPosition;

out vec4 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
uniform Light light;

uniform vec3 LightIntensity;

vec3 ads() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPosition - Position);
    vec3 viewDir = normalize(-Position);
    vec3 reflectDir = reflect(-lightDir, norm);

    return 
        light.ambient * material.ambient +
        light.diffuse * material.diffuse * max(dot(norm, lightDir), 0.0) +
        light.specular * material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
}

void main(){
    color=vec4(ads(), 1.0);
}
