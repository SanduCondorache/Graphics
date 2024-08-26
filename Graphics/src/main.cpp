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

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera camera((float)Width, (float)Height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;
    camera.SetScreenSize((float)Width, (float)Height);
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
        camera.MoveUp(cameraSpeed);
    }
    if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
        camera.MoveUp(-cameraSpeed);
    }

    camera.CameraRotate(yaw, pitch);
    camera.CameraMove(z, 0, x);
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

        VertexBuffer vb(vertices, sizeof(vertices));
        VertexArray vaCube;
        VertexArray vaLight;
        IndexBuffer ib(indeces, 6);

        VertexBufferLayout layoutCube;
        layoutCube.Push<float>(3);
        layoutCube.Push<float>(3);
        vaCube.AddBuffer(vb, layoutCube);

        VertexBufferLayout layoutLight;
        layoutLight.Push<float>(3);
        layoutLight.Push<float>(3);
        vaLight.AddBuffer(vb, layoutLight);

        Shader colorCube("res/ColorCube.shader");
        colorCube.Bind();

        Shader lightCube("res/LightCube.shader");
        lightCube.Bind();

        while (!glfwWindowShouldClose(window)) {

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            colorCube.Bind();
            colorCube.SetUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
            colorCube.SetUniform3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
            colorCube.SetUniform3f("lightPos", lightPos);

            glm::mat4 projection = camera.PerspectiveMatrix();
            glm::mat4 view = camera.ViewMatrix();

            colorCube.SetUniformMat4f("projection", projection);
            colorCube.SetUniformMat4f("view", view);

            glm::mat4 model = glm::mat4(1.0f);
            colorCube.SetUniformMat4f("model", model);

            vaCube.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            lightCube.Bind();
            lightCube.SetUniformMat4f("projection", projection);
            lightCube.SetUniformMat4f("view", view);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
            model = glm::scale(model, glm::vec3(0.2f));
            lightCube.SetUniformMat4f("model", model);

            vaLight.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}