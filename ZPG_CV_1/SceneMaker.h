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

#include "gift.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "plain.h"
#include "bushes.h"
#include "sphere.h"
#include "tree.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

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

		Scene* GetCurrentScene();

		vector<Scene*> GetAllScenes();

		void CreateSceneTriangle();

		void CreateSceneFourSpheresLight();

		void CreateSceneWithMoreModels();

		void CreateSceneForest();
};

