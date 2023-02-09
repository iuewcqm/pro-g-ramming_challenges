#include <stdio.h>
#include "shader/load_shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE  "test_window"

void init(void);
void init_glfw(void);
void init_window(void);
void init_glew(void);
void init_vertexbuffer(void);

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
  init();
  render();
  
  return 0;
}

void init(void) {
  init_glfw();
  init_window();
  init_glew();
  init_vertexbuffer();
}

void init_glfw(void) {
  if(!glfwInit())
    fprintf(stderr, "Failed to initialize GLFW\n");
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void init_window(void) {
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window");
    glfwTerminate();
  }
}

void init_glew(void) { 
  glfwMakeContextCurrent(window);
  glewExperimental=true;
  if(glewInit() != GLEW_OK)
    fprintf(stderr, "Failed to initialize GLEW\n");
}

void init_vertexbuffer(void) {
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void render(void) {
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  do {
    render_triangle();
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

void render_triangle(void) {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}
