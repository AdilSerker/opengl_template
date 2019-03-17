#version 330 core

in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 color;

uniform vec3 lightColor;
uniform vec3 objColor;

uniform vec3 viewPos;


void main(){
    float ambientCoef = 0.1;
    vec3 ambient = lightColor * ambientCoef;

    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(vLightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    float specCoef = 0.5;
    vec3 viewDir = normalize(-vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specCoef * spec * lightColor;


    vec3 result = (ambient + diffuse + specular) * objColor;
    color=vec4(result, 1.0);
}
