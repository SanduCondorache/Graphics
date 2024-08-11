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

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

using namespace std;

int Width = 800, Height = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera((float)Width, (float)Height, 10.0f);

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

        
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        

        while (!glfwWindowShouldClose(window)) {

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window);
            projection = camera.perspectiveMatrix(); //glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
            view = camera.viewMatrix(); //glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            shader.SetUniformMat4f("view", view);
            shader.SetUniformMat4f("projection", projection);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            va.Bind();
            ib.Bind();
            for (int i = 0; i < 10; i++) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.SetUniformMat4f("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}