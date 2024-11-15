#include "main.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

static unsigned int comple_shader(const std::string& source, unsigned int type) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    println("Failed to compile shader: " << message);
    glDeleteShader(id);
    return 0;
  }

  return id;
}

static unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = comple_shader(vertexShader, GL_VERTEX_SHADER);
  unsigned int fs = comple_shader(fragmentShader, GL_FRAGMENT_SHADER);

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

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

  std::string vertexShader = 
  R"(#version 330 core
    layout(location = 0) in vec4 position;
    void main() {
      gl_Position = position;
    }
  )";
  std::string fragmentShader = 
  R"(#version 330 core
    layout(location = 0) out vec4 color;
    void main() {
      color = vec4(1.0, 0.0, 0.0, 1.0);
    }
  )";
  unsigned int shader = create_shader(vertexShader, fragmentShader);
  glUseProgram(shader);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draws the buffer. (mode, starting index, # of vertices)
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(shader);
  glfwTerminate();
  return 0;
}