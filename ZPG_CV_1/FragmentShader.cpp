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
    this->shader =
        "#version 330 core\n"
        "in vec3 ourColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(ourColor, 1.0);\n" 
        "}\n";
}
