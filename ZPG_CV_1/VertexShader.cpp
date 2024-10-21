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
    this->shader = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;       
        layout(location = 1) in vec3 aNormal;    

        out vec3 FragPos;      
        out vec3 Normal;        

        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;
        uniform mat3 normalMatrix;  

        void main() {
            FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
            Normal = normalize(normalMatrix * aNormal);  

            gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
        }
    )";
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
