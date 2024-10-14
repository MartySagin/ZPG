#pragma once

#include <vector>
#include "Shader.h"
#include "Model.h"

using namespace std;

class Scene
{
public:
    vector<Shader> shaders;
    vector<Model> models;

    void Init();  
    void Render(); 
    void Update();  

    void AddShader(Shader shader);
    void AddModel(Model model);
};
