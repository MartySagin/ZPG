#include "Camera.h"
#include "ShaderProgram.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed, float fov, float aspectRatio, float zNear, float zFar)
    : position(position), target(target), up(up), movementSpeed(movementSpeed), fov(fov), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar)
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{  
    return this->viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::IncreaseMovementSpeed(float movementSpeed)
{
	this->movementSpeed += movementSpeed;
}

void Camera::DecreaseMovementSpeed(float movementSpeed)
{
	if (this->movementSpeed - movementSpeed < 1.0f) {
		this->movementSpeed = 1.0f;
		return;
    }
    
    this->movementSpeed -= movementSpeed;
}

void Camera::Rotate(float deltaX, float deltaY)
{
    yaw += deltaX;
    pitch += deltaY;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;


    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    target = glm::normalize(direction);

    UpdateViewMatrix();

    NotifyObservers();
}



void Camera::MoveForward(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    position += target * velocity;

    UpdateViewMatrix();

    NotifyObservers();
}

void Camera::MoveBackward(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    position -= target * velocity;

    UpdateViewMatrix();

    NotifyObservers();
}

void Camera::MoveLeft(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(target, up));

    position -= right * velocity;

    UpdateViewMatrix();

    NotifyObservers();
}

void Camera::MoveRight(float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(target, up));

    position += right * velocity;

    UpdateViewMatrix();

	NotifyObservers();
}



void Camera::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, position + target, up);
}

void Camera::UpdateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);  
}

void Camera::AddObserver(Observer* observer) {
    observers.push_back(observer);
}

void Camera::RemoveObserver(Observer* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::NotifyObservers() {
	for (auto& observer : observers) {
        observer->Update();
	}
}


