#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::vec3 position;   // Pozice kamery
    glm::vec3 target;     // Smìr, kam se kamera dívá
    glm::vec3 up;         // Smìr nahoru kamery

    float movementSpeed;  // Rychlost pohybu kamery

    float fov;            // Zorný úhel (Field of View)
    float aspectRatio;    // Pomìr stran okna
    float zNear, zFar;    // Blízké a vzdálené oøezové roviny

    glm::mat4 viewMatrix;       // Pohledová matice
    glm::mat4 projectionMatrix; // Projekèní matice

public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed, float fov, float aspectRatio, float zNear, float zFar);

    glm::mat4 GetViewMatrix() const;         // Vrací pohledovou matici
    glm::mat4 GetProjectionMatrix() const;   // Vrací projekèní matici

    void Rotate(float deltaX, float deltaY);

    void MoveForward(float deltaTime);

    void MoveBackward(float deltaTime);

    void MoveLeft(float deltaTime);

    void MoveRight(float deltaTime);

    void UpdateViewMatrix();      // Aktualizuje pohledovou matici
    void UpdateProjectionMatrix(); // Aktualizuje projekèní matici
};
