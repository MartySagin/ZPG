#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"

using namespace std;

class Scene
{
public:
    vector<DrawableObject*> objects;  

	Camera* camera;

	Light* light;

    void Init(vector<DrawableObject*> drawableObjects, Camera* camera, Light* light);  

    void Render();  

    void AddObject(DrawableObject* object);

    Camera* GetCamera();

    Light* GetLight();

};
