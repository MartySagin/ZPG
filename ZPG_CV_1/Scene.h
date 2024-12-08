#pragma once

#include <vector>
#include "DrawableObject.h"
#include "DrawableObjectOBJ.h"
#include "Camera.h"
#include "Light.h"
#include "Skybox.h"
#include "BezierCurve.h"

using namespace std;

class Scene
{
    private:
        vector<DrawableObject*> objects;  

	    Camera* camera;

	    vector<Light*> lights;

        Skybox* skybox;

		DrawableObject* selectedObject = nullptr;

        glm::vec3 selectedPosition;

		vector<glm::vec3> bezierControlPoints;

    public:
        void Init(Camera* camera, vector<Light*> lights);  

        void Render();  

        void AddObject(DrawableObject* object);

		void AddBezeirControlPoint(glm::vec3 controlPoint);

        void StartBezeirCurve();

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
