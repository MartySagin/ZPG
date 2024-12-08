#version 450

in vec3 SkyboxCoords;

uniform samplerCube textureUnit;

out vec4 fragColor;

void main() {
    fragColor = texture(textureUnit, SkyboxCoords);
}
