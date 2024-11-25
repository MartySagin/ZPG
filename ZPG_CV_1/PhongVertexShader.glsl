#version 330 core

layout(location = 0) in vec3 aPos;        // Position
layout(location = 1) in vec3 aNormal;     // Normal
layout(location = 2) in vec2 aTexCoords;  // Texture Coordinates
layout(location = 3) in vec3 aTangent;    // Tangent

out vec3 FragPos;        // Fragment position in world space
out vec2 TexCoords;      // Texture coordinates
out mat3 TBN;            // Tangent-Bitangent-Normal matrix for tangent space

uniform mat4 modelMatrix;       // Model transformation
uniform mat4 viewMatrix;        // View transformation
uniform mat4 projectionMatrix;  // Projection transformation

void main() {
    vec3 T = normalize(mat3(modelMatrix) * aTangent);
    vec3 N = normalize(mat3(modelMatrix) * aNormal);
    vec3 B = normalize(cross(N, T)); // Compute bitangent as cross product

    TBN = mat3(T, B, N); // Construct TBN matrix

    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    TexCoords = aTexCoords;

    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}
