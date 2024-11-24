#version 330 core

#define MAX_LIGHTS 4
#define OFF_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
#define DIRECTIONAL_LIGHT 3

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
    float ambientStrength;
    vec3 direction;
    float cutOff;   
    float outerCutOff;
    int type;
};

struct Material {
    float ra;
    float rd;
    float rs;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec3 objectColor;
uniform sampler2D textureUnit;
uniform bool hasTexture;

uniform float constant = 1.0;
uniform float linear = 0.09;
uniform float quadratic = 0.032;

void main() {
    vec3 norm = normalize(Normal);
    vec3 result = vec3(0.0); 

    for (int i = 0; i < numberOfLights; i++) {
        if (lights[i].type == OFF_LIGHT) {
            continue;
        }

        vec3 lightDir;
        float attenuation = 1.0;

        if (lights[i].type == DIRECTIONAL_LIGHT) {
            lightDir = normalize(-lights[i].direction);
        } else {
            lightDir = normalize(lights[i].position - FragPos);
            
            float distance = length(lights[i].position - FragPos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
        }

        vec3 ambient = material.ra * lights[i].ambientStrength * lights[i].color;

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = material.rd * diff * lights[i].color * lights[i].intensity;

        vec3 specular = vec3(0.0);
        
        if (dot(norm, lightDir) > 0.0) {
            vec3 viewDir = normalize(viewPosition - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
            specular = material.rs * spec * lights[i].color * lights[i].intensity;
        }

        if (lights[i].type == SPOT_LIGHT) {
            float theta = dot(lightDir, normalize(-lights[i].direction)); 
            float epsilon = lights[i].cutOff - lights[i].outerCutOff;                         
            float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0); 

            diffuse *= intensity;
            specular *= intensity;
            attenuation *= intensity;
        }

        vec3 lightEffect = (ambient + diffuse + specular) * attenuation;

        result += lightEffect;
    }

    vec3 texColor = hasTexture ? texture(textureUnit, TexCoords).rgb : objectColor; 

    result *= texColor;
    
    fragColor = vec4(result, 1.0);
}
