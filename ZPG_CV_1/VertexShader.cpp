#include "VertexShader.h"


VertexShader::VertexShader(const char* shader)
{
    this->shader = shader;
}

VertexShader::VertexShader()
{
    CreateNewShaderWithoutNormal();
}

const char* VertexShader::GetShader()
{
    return this->shader;
}

void VertexShader::SetShader(const char* shader)
{
    this->shader = shader;
}

void VertexShader::CreateNewShaderWithNormal()
{
    this->shader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aNormal;\n"
        "out vec3 ourNormal;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projectionMatrix;\n"
        "void main() {\n"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "    ourNormal = aNormal;\n"
        "}\n";
}


void VertexShader::CreateNewShaderWithoutNormal()
{
    this->shader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projectionMatrix;\n"
        "void main() {\n"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "    ourColor = aColor;\n"
        "}\n";
}
