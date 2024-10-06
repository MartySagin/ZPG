#pragma once

// Include GLEW
#include <GL/glew.h>
// Include GLFW  
#include <GLFW/glfw3.h>

class Model
{
	public:
        GLuint VBO;  
        GLuint VAO;  

        Model();

        void GenerateModel(float* points, GLsizeiptr size);

        void BindVAO();

        void UnbindVAO();

        void DeleteModel();
};

