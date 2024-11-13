#pragma once
#include <glm/glm.hpp>
#include "Subject.h"
#include "vector"
#include "Camera.h"

using namespace std;

class Light : public Subject, public Observer
{
    private:
        int index;
        
        glm::vec3 position;

        glm::vec3 color;

        float intensity;

        float ambientStrength;

        glm::vec3 direction;

		float cutOff;

		float outerCutOff;

        int type;

		vector<Observer*> observers;

    public:
        Light(glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, glm::vec3 direction, float cutOff, float outerCutOff, int type);

        glm::vec3 GetPosition();

        glm::vec3 GetColor();

        float GetIntensity();

		float GetAmbientStrength();

        glm::vec3 GetDirection();

		float GetCutOff();

		float GetOuterCutOff();

        int GetType();

        int GetIndex();

        void SetPosition(glm::vec3 newPosition);

        void SetColor(glm::vec3 newColor);

        void SetIntensity(float newIntensity);

        void SetAmbientStrength(float newAmbientStrength);

        void SetIndex(int index);

		void SetDirection(glm::vec3 newDirection);

		void SetCutOff(float newCutOff);

		void SetOuterCutOff(float newOuterCutOff);

		void NotifyObservers() override;

		void AddObserver(Observer* observer) override;

		void RemoveObserver(Observer* observer) override;

		void UpdateFromSubject(Subject* subject) override;
};
