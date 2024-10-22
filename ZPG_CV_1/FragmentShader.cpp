#include "FragmentShader.h"

#include <string>

using namespace std;


FragmentShader::FragmentShader(const char* shader)
{
    this->shader = shader;
}


FragmentShader::FragmentShader(glm::vec4 color)
{
    CreateNewShaderWithoutNormal(color);
}

FragmentShader::FragmentShader()
{
	CreateNewShaderWithNormal();
}

const char* FragmentShader::GetShader()
{
    return this->shader.c_str();
}


void FragmentShader::SetShader(const char* shader)
{
    this->shader = shader;
}


void FragmentShader::CreateNewShaderWithoutNormal(glm::vec4 color)
{
    
    string shaderCode =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(" +
        to_string(color.r) + ", " +
        to_string(color.g) + ", " +
        to_string(color.b) + ", " +
        to_string(color.a) + ");\n"
        "}\n";

    this->shader = shaderCode.c_str();
}

void FragmentShader::CreateNewShaderWithNormal()
{
    this->shader = R"(
        #version 330 core
        in vec3 FragPos;
        in vec3 Normal;

        out vec4 fragColor;

        uniform vec3 lightPosition;
        uniform vec3 lightColor;
        uniform float lightIntensity;
        uniform vec3 objectColor;

        void main() {
            // Ambient lighting
            float ambientStrength = 0.1;
            vec3 ambient = ambientStrength * lightColor;

            // Diffuse lighting
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPosition - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor * lightIntensity;

            // Combine lighting effects
            vec3 result = (ambient + diffuse) * objectColor;
            fragColor = vec4(result, 1.0);
        }
    )";
}
