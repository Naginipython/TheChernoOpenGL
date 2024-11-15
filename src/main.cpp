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

  // docs.gl

  float positions[6] = {
    -0.5f, -0.5f,
    +0.0f, +0.5f,
    +0.5f, -0.5f
  };

  // Buffer will just contain the data
  unsigned int buffer;
  // Creates id for a buffer
  glGenBuffers(1, &buffer);
  // Selects the buffer
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  // Gives data to the buffer. (data_type, size, data, usage)
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  // Controls what the attributes of the buffer are.
  glEnableVertexAttribArray(0);
  // At index 0, 2 floats, not normalized, 2 floats to get to next vertex, 0 offset
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draws the buffer. (mode, starting index, # of vertices)
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}