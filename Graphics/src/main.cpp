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
    glfwSwapInterval(2);
    glewInit();
    {
        Shader shader("res/Shader.shader");


        float vertices[] = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

        };

        float tex_coords[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f
        };
        std::cout << "LOH" << std::endl;
        VertexBuffer vb(vertices, sizeof(vertices));
        VertexArray va;

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);

        shader.Bind();

        while (!glfwWindowShouldClose(window)) {
            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            va.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}