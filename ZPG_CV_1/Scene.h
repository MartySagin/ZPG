#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"

using namespace std;

class Scene
{
public:
    vector<DrawableObject> objects;  

	Camera* camera;

    void Init(const vector<DrawableObject>& drawableObjects, Camera* camera);  
    void Render();  
    void Update();  

    void AddObject(DrawableObject object);

    Camera* GetCamera() const;

};
