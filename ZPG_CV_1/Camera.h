#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace std;

#include "Observer.h"
#include "Subject.h"

class ShaderProgram;

class Camera : Subject
{
private:
    glm::vec3 position;   
    glm::vec3 target;    
    glm::vec3 up;       

    float movementSpeed;  

    float fov;           
    float aspectRatio;   
    float zNear, zFar;    

    float yaw;    
    float pitch;

    glm::mat4 viewMatrix;       
    glm::mat4 projectionMatrix; 

    vector<Observer*> observers;

public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed, float fov, float aspectRatio, float zNear, float zFar);

    glm::mat4 GetViewMatrix(); 

    glm::mat4 GetProjectionMatrix();  

	glm::vec3 GetPosition();

	void IncreaseMovementSpeed(float movementSpeed);
	void DecreaseMovementSpeed(float movementSpeed);

    void Rotate(float deltaX, float deltaY);

    void MoveForward(float deltaTime);

    void MoveBackward(float deltaTime);

    void MoveLeft(float deltaTime);

    void MoveRight(float deltaTime);

    void UpdateViewMatrix();    
    void UpdateProjectionMatrix(); 

    void AddObserver(Observer* observer) override;

    void RemoveObserver(Observer* observer) override;

    void NotifyObservers() override;
};
