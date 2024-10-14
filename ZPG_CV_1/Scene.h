#pragma once

#include <vector>
#include "DrawableObject.h"

using namespace std;

class Scene
{
public:
    std::vector<DrawableObject> objects;  

    void Init(const vector<DrawableObject>& drawableObjects);  
    void Render();  
    void Update();  

    void AddObject(DrawableObject object);
};
