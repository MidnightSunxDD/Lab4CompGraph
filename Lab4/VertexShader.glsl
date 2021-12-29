//  VERTEX SHADER

#version 330 core

layout (location = 0) in vec3 vertex_position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(vertex_position, 1.0);
}