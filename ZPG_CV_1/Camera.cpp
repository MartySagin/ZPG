#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed, float fov, float aspectRatio, float zNear, float zFar)
    : position(position), target(target), up(up), movementSpeed(movementSpeed), fov(fov), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar)
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

void Camera::Rotate(float deltaX, float deltaY)
{
    
    target.x += deltaX;
    target.y += deltaY;

    if (target.y > 89.0f) target.y = 89.0f;
    if (target.y < -89.0f) target.y = -89.0f;

    UpdateViewMatrix();  
}

void Camera::MoveForward(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    position += target * velocity;  // Posun vpøed ve smìru cíle
    UpdateViewMatrix();  // Aktualizace pohledové matice
}

void Camera::MoveBackward(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    position -= target * velocity;  // Posun vzad
    UpdateViewMatrix();
}

void Camera::MoveLeft(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(target, up));  // Vektor doprava
    position -= right * velocity;  // Posun doleva
    UpdateViewMatrix();
}

void Camera::MoveRight(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(target, up));  // Vektor doprava
    position += right * velocity;  // Posun doprava
    UpdateViewMatrix();
}


void Camera::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, target, up);  // Vytvoøí pohledovou matici
}

void Camera::UpdateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);  // Vytvoøí projekèní matici
}
