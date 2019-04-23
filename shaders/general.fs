#version 330 core

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;
in vec3 LightPosition;

out vec4 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 LightIntensity;

vec3 ads() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPosition - Position);
    vec3 viewDir = normalize(-Position);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float diff = max(dot(norm, lightDir), 0.0);

    return 
        light.ambient * texture(material.diffuse, TexCoords).rgb +
        light.diffuse * diff * texture(material.diffuse, TexCoords).rgb +
        light.specular * spec * texture(material.specular, TexCoords).rgb;
}

void main(){
    color=vec4(ads(), 1.0);
}
