#version 330 core

in vec3 FragPos;        
in vec2 TexCoords;      
in mat3 TBN;            

uniform sampler2D textureUnit;  
uniform bool hasTexture;        
uniform vec3 objectColor;     

out vec4 fragColor;             

void main() {
    vec3 texColor = hasTexture ? texture(textureUnit, TexCoords).rgb : objectColor;

    fragColor = vec4(texColor, 1.0);
}
