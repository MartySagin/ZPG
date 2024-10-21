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

        uniform vec3 lightPosition = vec3(0.0, 0.0, 0.0);  
        uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);        
        uniform vec3 objectColor = vec3(0.385, 0.647, 0.812); 

        void main() {
            float ambientStrength = 0.35;
            vec3 ambient = ambientStrength * lightColor;

            vec3 lightDir = normalize(lightPosition - FragPos);  
            float diff = max(dot(Normal, lightDir), 0.0);      
            vec3 diffuse = diff * lightColor;

            vec3 result = (ambient + diffuse) * objectColor;
            fragColor = vec4(result, 1.0); 
        }
    )";
}
