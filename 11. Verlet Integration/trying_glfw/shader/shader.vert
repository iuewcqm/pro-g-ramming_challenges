#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;

void main() {
  gl_Position.xyz = vertexPosition_modelSpace;
  gl_Position.w   = 1.0;
}
