#version 330 core
out vec4 fragColor;

in vec2 TexCoords;

uniform vec3 objectColor;
uniform sampler2D textureUnit; 
uniform bool hasTexture; 

void main() {
    if (hasTexture) {
        fragColor = texture(textureUnit, TexCoords);
    }
    else {
        fragColor = vec4(objectColor, 1.0);
    }
}
