#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"
#include "Animation.h"
#include "Skybox.h"

using namespace std;

class Scene
{
    private:
        vector<DrawableObject*> objects;  

	    Camera* camera;

	    vector<Light*> lights;

		Animation animation;

        Skybox* skybox;

		DrawableObject* selectedObject = nullptr;

        glm::vec3 selectedPosition;

    public:
        void Init(Camera* camera, vector<Light*> lights);  

        void Render();  

        void Update(float deltaTime);

        void AddObject(DrawableObject* object);

		void AddAnimation(function<void(float)> animation);

        void SetSkybox(Skybox* skybox);

		void SetSelectedPosition(glm::vec3 position);

		void SelectObject(int objectID);

        void RemoveSelectedObject();

        void InsertObject(glm::vec3 position);

        Camera* GetCamera();

        vector<Light*> GetLights();

		vector<DrawableObject*> GetObjects();

        Skybox* GetSkybox();

		glm::vec3 GetSelectedPosition();
};
