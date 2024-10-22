#pragma once
#include <glm/glm.hpp>
#include "Subject.h"

class Light : public Subject
{
    private:
        glm::vec3 position;

        glm::vec3 color;

        float intensity;

    public:
        Light(const glm::vec3& position, const glm::vec3& color, float intensity);

        glm::vec3 GetPosition() const;

        glm::vec3 GetColor() const;

        float GetIntensity() const;

        void SetPosition(const glm::vec3& newPosition);

        void SetColor(const glm::vec3& newColor);

        void SetIntensity(float newIntensity);
};
