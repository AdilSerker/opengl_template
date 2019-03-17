#version 330 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 normal;

uniform mat4 M;
uniform mat3 N;
uniform mat4 V;
uniform mat4 P;

uniform vec3 lightPos;

out vec3 vNormal;
out vec3 vFragPos;
out vec3 vLightPos;

void main(){
    gl_Position=P*V*M*vec4(position,1.);
    vLightPos = vec3(V * vec4(lightPos, 1.0));
    vFragPos = vec3(V * M*vec4(position,1.));
    vNormal = mat3(transpose(inverse(V * M))) * normal;
}
