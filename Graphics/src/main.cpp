#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

int Width = 800, Height = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera((float)Width, (float)Height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;
    camera.setScreenSize((float)Width, (float)Height);
}

void processInput(GLFWwindow* window) {
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = camera.getCameraSpeed() * deltaTime;
    float cameraSensitivity = 10.0f * deltaTime;

    float x = 0.0f, z = 0.0f;
    float yaw = ((float)Mouse::getMouseDX()) * cameraSensitivity;
    float pitch = ((float)Mouse::getMouseDY()) * cameraSensitivity;

    if (Keyboard::key(GLFW_KEY_W)) {
        z = cameraSpeed;
    }
    if (Keyboard::key(GLFW_KEY_S)) {
        z = -cameraSpeed;
    }
    if (Keyboard::key(GLFW_KEY_D)) {
        x = cameraSpeed;
    }
    if (Keyboard::key(GLFW_KEY_A)) {
        x = -cameraSpeed;
    }
    if (Keyboard::key(GLFW_KEY_SPACE)) {
        camera.moveUp(cameraSpeed);
    }
    if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
        camera.moveUp(-cameraSpeed);
    }

    camera.cameraRotate(yaw, pitch);
    camera.cameraMove(z, 0, x);
}


int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(Width, Height, "Loh", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, Keyboard::keyCallback);
    glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
    glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::mouseWheelCallback);
    {
        glEnable(GL_DEPTH_TEST);
        
        Renderer renderer;

        VertexBuffer vb(vertices, sizeof(vertices));
        VertexArray va;
        IndexBuffer ib(indeces, 6);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        Shader shader("res/Shader.shader");
        shader.Bind();

        Texture texture1("Textures/wall.jpg");
        Texture texture2("Textures/face.png");
        texture1.Bind(0);
        texture2.Bind(1);
        shader.SetUniform1i("u_Texture1", 0);
        shader.SetUniform1i("u_Texture2", 1);

        while (!glfwWindowShouldClose(window)) {

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window);

            renderer.Clear();
            renderer.Draw(va, shader, camera);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}