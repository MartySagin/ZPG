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

glm::vec3 Camera::GetPosition()
{
    return this->position;
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
    this->yaw += deltaX;
    this->pitch += deltaY;

    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;


    glm::vec3 direction;

    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->target = glm::normalize(direction);

    UpdateViewMatrix();

    NotifyObservers();
}



void Camera::MoveForward(float deltaTime)
{
    float velocity = this->movementSpeed * deltaTime;

    this->position += this->target * velocity;

    UpdateViewMatrix();

    NotifyObservers();
}

void Camera::MoveBackward(float deltaTime)
{
    float velocity = this->movementSpeed * deltaTime;

    this->position -= this->target * velocity;

    UpdateViewMatrix();

    NotifyObservers();
}

void Camera::MoveLeft(float deltaTime)
{
    float velocity = this->movementSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(this->target, this->up));

    this->position -= right * velocity;

    UpdateViewMatrix();

    NotifyObservers();
}

void Camera::MoveRight(float deltaTime)
{
    float velocity = this->movementSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(this->target, this->up));

    this->position += right * velocity;

    UpdateViewMatrix();

	NotifyObservers();
}



void Camera::UpdateViewMatrix()
{
    this->viewMatrix = glm::lookAt(this->position, this->position + this->target, this->up);
}

void Camera::UpdateProjectionMatrix()
{
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->aspectRatio, this->zNear, this->zFar);
}

void Camera::AddObserver(Observer* observer) {
    this->observers.push_back(observer);
}

void Camera::RemoveObserver(Observer* observer) {
    this->observers.erase(remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
}

void Camera::NotifyObservers() {
	for (auto& observer : this->observers) {
        observer->UpdateFromSubject();
	}
}


