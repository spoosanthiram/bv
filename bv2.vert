#version 430 core

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec3 vertex_normal;

uniform mat4 projection_matrix;
uniform mat4 model_view_matrix;

out vec4 vertex;
out vec4 normal;

void main()
{
  vertex = model_view_matrix * vertex_position;
  normal = model_view_matrix * vec4(vertex_normal, 0.0);

  gl_Position = projection_matrix * vertex;
}
