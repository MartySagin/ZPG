#pragma once

#include <random>

#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "Translate.h"
#include "Skybox.h"
#include "DrawableObjectOBJ.h"

#include "models/gift.h"
#include "models/suzi_flat.h"
#include "models/suzi_smooth.h"
#include "models/plain.h"
#include "models/bushes.h"
#include "models/sphere.h"
#include "models/tree.h"
#include "models/skycube.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <SOIL.h>

class SceneMaker
{
	private:
		vector<Scene*> scenes;

		int currentSceneIndex;

		float ratio;

	public:
		SceneMaker(float ratio);

		void AddScene(Scene* scene);

		void SwitchScene();

		void InitObservers(Camera* camera, vector<Light*> lights, vector<ShaderProgram*> shaders);

		Scene* GetCurrentScene();

		vector<Scene*> GetAllScenes();

		void CreateSceneTriangle();

		void CreateSceneFourSpheresLight();

		void CreateSceneWithMoreModels();

		void CreateSceneForest();

		void CreateSceneForestDark();
};

