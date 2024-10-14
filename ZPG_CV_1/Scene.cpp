#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>
#include "tree.h"
#include "bushes.h"

void Scene::Init()
{
    
}

void Scene::Render()
{
   
    for (size_t i = 0; i < models.size(); ++i)
    {
        shaders[i].UseProgram();  
        models[i].BindVAO();      
        shaders[i].Draw();       
        models[i].UnbindVAO();    
    }
}

void Scene::Update()
{
    //Empty for now
}

void Scene::AddShader(Shader shader)
{
    this->shaders.push_back(shader);
}

void Scene::AddModel(Model model)
{
    this->models.push_back(model);
}
