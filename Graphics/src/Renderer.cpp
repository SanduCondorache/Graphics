#include "Renderer.h"

#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGl error] (" << error << "):" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}


void Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, Shader shader, const Camera& camera) const {

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.perspectiveMatrix();
    view = camera.viewMatrix();
    shader.SetUniformMat4f("view", view);
    shader.SetUniformMat4f("projection", projection);

    va.Bind();
    for (int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}