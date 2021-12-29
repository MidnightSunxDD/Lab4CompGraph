//  FRAGMENT SHADER

#version 330 core

uniform vec3 VertexColor;

out vec4 color;

void main()
{
	color = vec4(VertexColor, 1.0f);
}