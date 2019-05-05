#version 330 core

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;
in vec3 LightPosition;
in vec3 LightDirection;

out vec4 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLight;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

vec3 point_ads() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPosition - Position);
    vec3 viewDir = normalize(-Position);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    float diff = max(dot(norm, lightDir), 0.0);

    float distance    = length(LightPosition - Position);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + 
    		    pointLight.quadratic * (distance * distance));

    return 
        pointLight.ambient * texture(texture_diffuse1, TexCoords).rgb * attenuation +
        pointLight.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb * attenuation +
        dirLight.specular * spec * texture(texture_specular1, TexCoords).rgb;
}

vec3 dirLight_ads() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-LightDirection);
    vec3 viewDir = normalize(-Position);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    float diff = max(dot(norm, lightDir), 0.0);

    return 
        dirLight.ambient * texture(texture_diffuse1, TexCoords).rgb +
        dirLight.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb +
        dirLight.specular * spec * texture(texture_specular1, TexCoords).rgb;
}

void main(){
    vec3 res;

    res = point_ads() + dirLight_ads();

    color=vec4(res, 1.0);
}
