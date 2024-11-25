#version 450

layout(location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool followCamera; 

out vec3 FragPos;

void main() {
    mat4 effectiveViewMatrix = followCamera ? mat4(mat3(viewMatrix)) : viewMatrix;

    gl_Position = projectionMatrix * effectiveViewMatrix * modelMatrix * vec4(aPos, 1.0);
    FragPos = aPos;
}
