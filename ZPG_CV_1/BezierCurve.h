#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"

class BezierCurve : public TransformationComponent {
private:
    glm::mat4 bezierMatrix;    

    glm::mat4x3 controlPoints; 

    float t;              

    float delta;      

    bool loop;      

	bool completedOneCycle;         

public:
    BezierCurve(glm::mat4x3 controlPoints, float speed, bool loop = true);

    glm::mat4 GetMatrix() override;

    void SetControlPoints(glm::mat4x3 newControlPoints);
    void SetSpeed(float newSpeed);
};
