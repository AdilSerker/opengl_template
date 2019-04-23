#version 330 core

layout(location=0)in vec3 VertexPosition;
layout(location=1)in vec3 VertexNormal;
layout(location=2)in vec2 VertexTexCoords;

uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

out vec3 Normal;
out vec3 Position;
out vec2 TexCoords;
out vec3 LightPosition;


void main(){

    Position = vec3(ViewMatrix * ModelMatrix*vec4(VertexPosition,1.));
    LightPosition = vec3(ViewMatrix * vec4(light.position,1.));
    TexCoords = VertexTexCoords;

    Normal = NormalMatrix * VertexNormal;

    gl_Position=ProjMatrix*ViewMatrix*ModelMatrix*vec4(VertexPosition,1.);
}
