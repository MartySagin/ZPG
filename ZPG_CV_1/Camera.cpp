#include "Camera.h"
#include "ShaderProgram.h"

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
    position += target * velocity; 
    UpdateViewMatrix();  
}

void Camera::MoveBackward(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    position -= target * velocity; 
    UpdateViewMatrix();
}

void Camera::MoveLeft(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(target, up));  
    position -= right * velocity;  
    UpdateViewMatrix();
}

void Camera::MoveRight(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(target, up)); 
    position += right * velocity;  
    UpdateViewMatrix();
}


void Camera::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, target, up);  
}

void Camera::UpdateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);  
}

void Camera::AddObserver(ShaderProgram* observer) {
    observers.push_back(observer);
}

void Camera::RemoveObserver(ShaderProgram* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::NotifyObservers() {
    for (ShaderProgram* observer : observers) {
        observer->UpdateFromCamera(); 
    }
}