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

	    vector<Light*> lights;

    public:
        void Init(vector<DrawableObject*> drawableObjects, Camera* camera, vector<Light*> lights);  

        void Render();  

        void AddObject(DrawableObject* object);

        Camera* GetCamera();

        vector<Light*> GetLights();

		vector<DrawableObject*> GetObjects();

};
