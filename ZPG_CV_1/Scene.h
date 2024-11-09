#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"
#include "Animation.h"

using namespace std;

class Scene
{
    private:
        vector<DrawableObject*> objects;  

	    Camera* camera;

	    vector<Light*> lights;

		Animation animation;

    public:
        void Init(vector<DrawableObject*> drawableObjects, Camera* camera, vector<Light*> lights);  

        void Render();  

        void Update(float deltaTime);

        void AddObject(DrawableObject* object);

		void AddAnimation(function<void(float)> animation);

        Camera* GetCamera();

        vector<Light*> GetLights();

		vector<DrawableObject*> GetObjects();

};
