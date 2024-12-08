#include "Controller.h"
#include "Application.h"
#include <cstdio>

bool Controller::mouseRightButtonPressed = false;
bool Controller::firstMouse = true;
bool Controller::addToBezeir = false;

Controller::Controller()
{
	
}

void Controller::ErrorCallback(int error, const char* description) {
    fputs(description, stderr);
}

void Controller::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application* app = (Application*) (glfwGetWindowUserPointer(window));

    Scene* currentScene = app->GetSceneMaker()->GetCurrentScene();

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_LEFT) MoveLight(window, 0);
        else if (key == GLFW_KEY_RIGHT) MoveLight(window, 1);
        else if (key == GLFW_KEY_UP) MoveLight(window, 2);
        else if (key == GLFW_KEY_DOWN) MoveLight(window, 3);
        else if (key == GLFW_KEY_SPACE) app->GetSceneMaker()->SwitchScene();
        else if (key == GLFW_KEY_H) {
            if (Skybox* skybox = currentScene->GetSkybox()) {
                skybox->SetFollowCamera(skybox->GetFollowCamera());

                Camera* camera = currentScene->GetCamera();

                if (!skybox->GetFollowCamera()) {
                    camera->RemoveObserver(skybox);
                }
                else {
                    camera->AddObserver(skybox);
                }
            }
		}
        else if (key == GLFW_KEY_DELETE) {
            currentScene->RemoveSelectedObject();
        }
        else if (key == GLFW_KEY_INSERT) {
            currentScene->InsertObject(currentScene->GetSelectedPosition());
        }
        else if (key == GLFW_KEY_B) {
			addToBezeir = !addToBezeir;

            currentScene->ResetBezeirControlPoints();

			cout << "addToBezeir: " << addToBezeir << endl;
        }
    }

    if (Camera * camera = app->GetSceneMaker()->GetCurrentScene()->GetCamera()) {

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
		if (Camera* camera = scene->GetCamera()) {
            camera->SetAspectRatio((float)width / (float)height);
            
            camera->SetWidth(width);

            camera->SetHeight(height);
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
    else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			Application* app = (Application*)(glfwGetWindowUserPointer(window));
            
            GLdouble cursor_x, cursor_y;

            glfwGetCursorPos(window, &cursor_x, &cursor_y);

            GLbyte color[4];
            GLfloat depth;
            GLuint index;

            GLint x = (GLint)cursor_x;
            GLint y = (GLint)cursor_y;

            Scene* currentScene = app->GetSceneMaker()->GetCurrentScene();

            Camera* camera = currentScene->GetCamera();

			int newy = camera->GetHeight() - y;

            glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
            glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth% f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

            glm::vec3 screenX = glm::vec3(x, newy, depth);
            glm::mat4 view = camera->GetViewMatrix();
            glm::mat4 projection = camera->GetProjectionMatrix();
            glm::vec4 viewPort = glm::vec4(0, 0, camera->GetWidth(), camera->GetHeight());
            glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

            printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

            if (!addToBezeir) {
                currentScene->SelectObject(index);
            }

            currentScene->SetSelectedPosition(pos);

            if (addToBezeir) {
                currentScene->AddBezeirControlPoint(pos);
            }
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
            light->SetPosition(light->GetPosition() + glm::vec3(0.0f, 0.0f, -0.1f));
        }
        else if (direction == 3) {
            light->SetPosition(light->GetPosition() + glm::vec3(0.0f, 0.0f, 0.1f));
        }

    }
    
}

