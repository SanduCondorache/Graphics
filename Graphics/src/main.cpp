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


int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Loh", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();
    {

        float vertices[] = {
            // positions         // colors         // texture_coords
             0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,     // top right
             0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,     // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,     // bottom left 
            -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f      // top left
        };

        size_t indeces[] = {
            0, 1, 2,
            2, 3, 0
        };
        
        VertexBuffer vb(vertices, sizeof(vertices));
        VertexArray va;
        IndexBuffer ib(indeces, 6);

        VertexBufferLayout layout;
        layout.Push<float>(3);
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
        
        float mixValue = 0.01f;
        while (!glfwWindowShouldClose(window)) {

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            
            shader.Bind();
            shader.SetUniform1f("t_Value", mixValue);
            va.Bind();
            ib.Bind();
            glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
            glfwSwapBuffers(window);
            glfwPollEvents();
            mixValue += 0.01f;
            if (mixValue >= 1.0f) {
                mixValue = 0.0f;
            }
        }
    }
    glfwTerminate();
    return 0;
}