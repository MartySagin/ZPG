#version 450

in vec3 FragPos;

uniform samplerCube textureUnit;

out vec4 fragColor;

void main() {
    fragColor = texture(textureUnit, FragPos);
}
