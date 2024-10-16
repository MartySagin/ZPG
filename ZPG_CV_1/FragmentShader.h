#pragma once

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <string>

using namespace std;

class FragmentShader
{
	public:
		string shader;

		FragmentShader(const char* shader);
		FragmentShader(glm::vec4 color);
		FragmentShader();

		const char* GetShader();
		void SetShader(const char* shader);

		void CreateNewShaderWithoutNormal(glm::vec4 color);
		void CreateNewShaderWithNormal();
};

