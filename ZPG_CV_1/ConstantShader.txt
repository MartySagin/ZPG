#version 330 core
    out vec4 fragColor;

    uniform vec3 objectColor = vec3(0.385, 0.647, 0.812);

    void main() {
        fragColor = vec4(objectColor, 1.0);
    }