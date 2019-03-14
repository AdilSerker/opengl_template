#version 330 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 color;
layout(location=2)in vec2 texCoord;

uniform mat4 transform;

out vec3 vColor;
out vec2 vTexCoord;

mat4 rotationMatrix(vec3 axis,float angle)
{
    axis=normalize(axis);
    float s=sin(angle);
    float c=cos(angle);
    float oc=1.-c;
    
    return mat4(oc*axis.x*axis.x+c,oc*axis.x*axis.y-axis.z*s,oc*axis.z*axis.x+axis.y*s,0.,
        oc*axis.x*axis.y+axis.z*s,oc*axis.y*axis.y+c,oc*axis.y*axis.z-axis.x*s,0.,
        oc*axis.z*axis.x-axis.y*s,oc*axis.y*axis.z+axis.x*s,oc*axis.z*axis.z+c,0.,
    0.,0.,0.,1.);
}

void main(){
    vColor=color;
    vTexCoord=texCoord;
    gl_Position=transform*vec4(position,1.);
    
}
