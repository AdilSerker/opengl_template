#version 330 core

layout(location=0)in vec3 VertexPosition;
layout(location=1)in vec3 VertexNormal;

uniform mat4 M;
uniform mat3 N;
uniform mat4 V;
uniform mat4 P;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
uniform Light light;

out vec3 Normal;
out vec3 Position;
out vec3 LightPosition;


void main(){

    Position = vec3(V * M*vec4(VertexPosition,1.));
    LightPosition = vec3(V * vec4(light.position,1.));

    Normal = N * VertexNormal;


    gl_Position=P*V*M*vec4(VertexPosition,1.);
}
