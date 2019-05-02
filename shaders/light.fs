#version 330 core

in vec3 Normal;
in vec3 Position;
in vec3 LightPosition;

out vec4 color;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
uniform Light pointLight;

uniform vec3 LightIntensity;

void main(){
    color=vec4(pointLight.diffuse, 1.0);
}
