#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shader/load_shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// using namespace glm;

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE  "test_window"

void glfw_init(void);
void render(void);
void render_triangle(void);

GLFWwindow *window;
GLuint vertexbuffer;

static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main(void) {
  glfw_init();

  render();
  
  return 0;
}

void glfw_init(void) {
  // init glfw
  if(!glfwInit())
    fprintf(stderr, "Failed to initialize GLFW\n");
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  
  // init window
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window");
    glfwTerminate();
  }
  
  // init glew
  glfwMakeContextCurrent(window);
  glewExperimental=true;
  if(glewInit() != GLEW_OK)
    fprintf(stderr, "Failed to initialize GLEW\n");

  // init vertex array
  // GLuint vertex_array_id;
  // glGenVertexArrays(1, &vertex_array_id);
  // glBindVertexArray(vertex_array_id);
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void render(void) {
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  do {
    glClear(GL_COLOR_BUFFER_BIT);
    render_triangle();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

void render_triangle(void) {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
    0,        // someshit
    3,        // size
    GL_FLOAT, // type
    GL_FALSE, // normalized?
    0,        // stride
    (void*)0  // array buffer offset
  );

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}
