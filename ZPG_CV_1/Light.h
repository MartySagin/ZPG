#pragma once
#include <glm/glm.hpp>
#include "Subject.h"
#include "vector"

using namespace std;

class Light : public Subject
{
    private:
        glm::vec3 position;

        glm::vec3 color;

        float intensity;

        float ambientStrength;

		vector<Observer*> observers;

    public:
        Light(glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength);

        glm::vec3 GetPosition();

        glm::vec3 GetColor();

        float GetIntensity();

		float GetAmbientStrength();

        void SetPosition(glm::vec3 newPosition);

        void SetColor(glm::vec3 newColor);

        void SetIntensity(float newIntensity);

        void SetAmbientStrength(float newAmbientStrength);

		void NotifyObservers() override;

		void AddObserver(Observer* observer) override;

		void RemoveObserver(Observer* observer) override;
};
