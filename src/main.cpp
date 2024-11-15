#include "main.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]) {
  if (!glfwInit()) {
    println("Failed to initialize GLFW");
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    println("Failed to create window");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    println("Failed to initialize GLEW");
    return -1;
  }

  println(glGetString(GL_VERSION));

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}