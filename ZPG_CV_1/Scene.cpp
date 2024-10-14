#include "Scene.h"

void Scene::Init(const std::vector<DrawableObject>& drawableObjects)
{
    for (const auto& object : drawableObjects)
    {
        this->objects.push_back(object); 
    }
}

void Scene::Render()
{
    for (auto& object : objects)
    {
        object.Draw();  
    }
}

void Scene::Update()
{

    for (auto& object : objects)
    {
        // Zde mùžeš pøidat dynamické aktualizace (napø. rotace)
        object.SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));  // Pro jednoduchý pøíklad rotace
    }
}

void Scene::AddObject(DrawableObject object)
{
    objects.push_back(object);
}
