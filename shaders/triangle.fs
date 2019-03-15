#version 330 core

in vec2 vTexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform float mixf;

void main(){
    color=mix(
        texture(ourTexture1,vec2(vTexCoord.x,1.-vTexCoord.y)),
        texture(ourTexture2,vTexCoord),
        mixf
    );
}
