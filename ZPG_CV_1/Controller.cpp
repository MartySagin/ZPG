#include "Controller.h"
#include "Application.h"
#include <cstdio>

bool Controller::mouseRightButtonPressed = false;
bool Controller::firstMouse = true;

Controller::Controller()
{
	
}

void Controller::ErrorCallback(int error, const char* description) {
    fputs(description, stderr);
}

void Controller::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application* app = (Application*) (glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_LEFT) MoveLight(window, 0);
        else if (key == GLFW_KEY_RIGHT) MoveLight(window, 1);
        else if (key == GLFW_KEY_UP) MoveLight(window, 2);
        else if (key == GLFW_KEY_DOWN) MoveLight(window, 3);
        else if (key == GLFW_KEY_R) RotateObject(window, 0);
        else if (key == GLFW_KEY_T) RotateObject(window, 1);
        else if (key == GLFW_KEY_Y) RotateObject(window, 2);
        else if (key == GLFW_KEY_SPACE) app->GetSceneMaker()->SwitchScene();
        else if (key == GLFW_KEY_H) {
            app->GetSceneMaker()->GetCurrentScene()->GetSkybox()->SetFollowCamera(!app->GetSceneMaker()->GetCurrentScene()->GetSkybox()->GetFollowCamera());

            if (!app->GetSceneMaker()->GetCurrentScene()->GetSkybox()->GetFollowCamera()) {
                app->GetSceneMaker()->GetCurrentScene()->GetSkybox()->GetTransformation()->AddComponent(new Translate(app->GetSceneMaker()->GetCurrentScene()->GetCamera()->GetPosition()));
            }
            else {
                app->GetSceneMaker()->GetCurrentScene()->GetSkybox()->GetTransformation()->ClearComponents();
            }
        }
    }

    if (app->GetSceneMaker()->GetCurrentScene()->GetCamera()) {
        Camera* camera = app->GetSceneMaker()->GetCurrentScene()->GetCamera();

        static float lastFrameTime = 0.0f;

        float currentFrameTime = (float)glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;

        if (deltaTime > 0.01f) {
            deltaTime = 0.01f;
        }

        lastFrameTime = currentFrameTime;

        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (key == GLFW_KEY_W) camera->MoveForward(deltaTime);
            else if (key == GLFW_KEY_S) camera->MoveBackward(deltaTime);
            else if (key == GLFW_KEY_A) camera->MoveLeft(deltaTime);
            else if (key == GLFW_KEY_D) camera->MoveRight(deltaTime);
        }

        if (key == GLFW_KEY_U && action == GLFW_PRESS) camera->IncreaseMovementSpeed(2.0f);
        if (key == GLFW_KEY_J && action == GLFW_PRESS) camera->DecreaseMovementSpeed(2.0f);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}

void Controller::WindowFocusCallback(GLFWwindow* window, int focused) {
    printf("window_focus_callback \n");
}

void Controller::WindowIconifyCallback(GLFWwindow* window, int iconified) {
    printf("window_iconify_callback \n");
}

void Controller::WindowSizeCallback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);

    glViewport(0, 0, width, height);

    Application* app = (Application*) (glfwGetWindowUserPointer(window));

	for (auto& scene : app->GetSceneMaker()->GetAllScenes()) {
		if (scene->GetCamera()) {
			scene->GetCamera()->SetAspectRatio((float)width / (float)height);
		}
	}
}

void Controller::CursorCallback(GLFWwindow* window, double x, double y) {
    if (mouseRightButtonPressed) {
        Application* app = (Application*) (glfwGetWindowUserPointer(window));

        Camera* camera = app->GetSceneMaker()->GetCurrentScene()->GetCamera();

        static double lastX = 400, lastY = 300;

        if (firstMouse) {
            lastX = x;
            lastY = y;

            firstMouse = false;
        }

        double offsetX = x - lastX;
        double offsetY = lastY - y;

        lastX = x;
        lastY = y;

        float sensitivity = 0.1f;

        offsetX *= sensitivity;
        offsetY *= sensitivity;

        camera->Rotate((float)offsetX, (float)offsetY);
    }
}

void Controller::ButtonCallback(GLFWwindow* window, int button, int action, int mode) {
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			mouseRightButtonPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			mouseRightButtonPressed = false;

			firstMouse = true;
        }
    }
}

void Controller::MoveLight(GLFWwindow* window, int direction)
{
    Application* app = (Application*) (glfwGetWindowUserPointer(window));

    for (auto& light : app->GetSceneMaker()->GetCurrentScene()->GetLights()) {

        if (direction == 0) {
            light->SetPosition(light->GetPosition() + glm::vec3(-0.1f, 0.0f, 0.0f));
        }
        else if (direction == 1) {
            light->SetPosition(light->GetPosition() + glm::vec3(0.1f, 0.0f, 0.0f));
        }
        else if (direction == 2) {
            light->SetPosition(light->GetPosition() + glm::vec3(0.0f, 0.1f, 0.0f));
        }
        else if (direction == 3) {
            light->SetPosition(light->GetPosition() + glm::vec3(0.0f, -0.1f, 0.0f));
        }

    }
    
}

void Controller::RotateObject(GLFWwindow* window, int axis)
{
    Application* app = (Application*) (glfwGetWindowUserPointer(window));

    for (auto& object : app->GetSceneMaker()->GetCurrentScene()->GetObjects())
    {
        if (axis == 0) {
            object->GetTransformation()->AddComponent(new Rotate(glm::vec3(0.0f, 0.0f, 5.0f)));
        }
        else if (axis == 1) {
            object->GetTransformation()->AddComponent(new Rotate(glm::vec3(0.0f, 5.0f, 0.0f)));
        }
		else if (axis == 2) {
			object->GetTransformation()->AddComponent(new Rotate(glm::vec3(5.0f, 0.0f, 0.0f)));
		}
    }
}
