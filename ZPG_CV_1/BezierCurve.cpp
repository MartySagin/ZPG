#include "BezierCurve.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

BezierCurve::BezierCurve(glm::mat4x3 controlPoints, float speed, bool loop)
    : controlPoints(controlPoints), loop(loop), t(0.0f), delta(speed) {

    this->bezierMatrix = glm::mat4(
        glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0.0),
        glm::vec4(-3.0, 3.0, 0.0, 0.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    );

    this->completedOneCycle = false; 
}

glm::mat4 BezierCurve::GetMatrix() {

    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

    glm::vec3 position = parameters * this->bezierMatrix * glm::transpose(this->controlPoints);

    if (this->loop || !this->completedOneCycle) {
        this->t += this->delta;

        if (this->t >= 1.0f || this->t <= 0.0f) {
            this->delta *= -1;

            if (!this->loop && this->t <= 0.0f) {
                this->completedOneCycle = true;

                this->t = 0.0f;

                this->delta = 0.0f;
            }

            this->t = glm::clamp(this->t, 0.0f, 1.0f);
        }
    }

    glm::mat4 result = glm::mat4(1.0f);

    result = glm::translate(result, position);

    return result;
}

void BezierCurve::SetControlPoints(glm::mat4x3 newControlPoints) {
    this->controlPoints = newControlPoints;
}

void BezierCurve::SetSpeed(float newSpeed) {
    this->delta = (this->delta > 0 ? newSpeed : -newSpeed);
}
