#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"

using namespace std;

class Scene
{
    private:
        vector<DrawableObject*> objects;  

	    Camera* camera;

	    Light* light;

    public:
        void Init(vector<DrawableObject*> drawableObjects, Camera* camera, Light* light);  

        void Render();  

        void AddObject(DrawableObject* object);

        Camera* GetCamera();

        Light* GetLight();

		vector<DrawableObject*> GetObjects();

};
