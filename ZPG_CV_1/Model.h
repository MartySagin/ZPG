#pragma once

// Include GLEW
#include <GL/glew.h>
// Include GLFW  
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Model
{
	private:
        GLuint VAO;
        GLuint VBO;
		GLuint EBO;

		int indicesCount;

        struct Vertex {
            float Position[3];
            float Normal[3];
            float Texture[2];
            float Tangent[3];
        };

    public:
        Model();

        void GenerateModel(const float* points, GLsizeiptr size);
        void GenerateModelWithNormal(const float* points, GLsizeiptr size);
        void GenerateModelWithNormalAndUV(const float* points, GLsizeiptr size);
		bool GenerateModelFromOBJ(const char* fileName);

		int GetIndicesCount();

        void BindVAO();
        void UnbindVAO();
        void DeleteModel();
};

