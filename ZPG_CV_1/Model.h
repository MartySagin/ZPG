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
	public:
        GLuint VAO;
        GLuint VBO;

        Model();

        void GenerateModel(const float* points, GLsizeiptr size);
        void GenerateModelWithNormal(const float* points, GLsizeiptr size);

        void BindVAO();
        void UnbindVAO();
        void DeleteModel();
};

