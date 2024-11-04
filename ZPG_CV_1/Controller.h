#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>



class Controller {
    private:
		static bool mouseRightButtonPressed;
        static bool firstMouse;

    public:
        Controller();

        static void ErrorCallback(int error, const char* description);

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void WindowFocusCallback(GLFWwindow* window, int focused);

        static void WindowIconifyCallback(GLFWwindow* window, int iconified);

        static void WindowSizeCallback(GLFWwindow* window, int width, int height);

        static void CursorCallback(GLFWwindow* window, double x, double y);

        static void ButtonCallback(GLFWwindow* window, int button, int action, int mode);

        static void MoveLight(GLFWwindow* window, int direction);

        static void RotateObject(GLFWwindow* window, int axis);
};
