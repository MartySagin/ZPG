#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::vec3 position;   // Pozice kamery
    glm::vec3 target;     // Sm�r, kam se kamera d�v�
    glm::vec3 up;         // Sm�r nahoru kamery

    float movementSpeed;  // Rychlost pohybu kamery

    float fov;            // Zorn� �hel (Field of View)
    float aspectRatio;    // Pom�r stran okna
    float zNear, zFar;    // Bl�zk� a vzd�len� o�ezov� roviny

    glm::mat4 viewMatrix;       // Pohledov� matice
    glm::mat4 projectionMatrix; // Projek�n� matice

public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float movementSpeed, float fov, float aspectRatio, float zNear, float zFar);

    glm::mat4 GetViewMatrix() const;         // Vrac� pohledovou matici
    glm::mat4 GetProjectionMatrix() const;   // Vrac� projek�n� matici

    void Rotate(float deltaX, float deltaY);

    void MoveForward(float deltaTime);

    void MoveBackward(float deltaTime);

    void MoveLeft(float deltaTime);

    void MoveRight(float deltaTime);

    void UpdateViewMatrix();      // Aktualizuje pohledovou matici
    void UpdateProjectionMatrix(); // Aktualizuje projek�n� matici
};
