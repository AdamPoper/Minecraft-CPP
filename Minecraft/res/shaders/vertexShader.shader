#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec4 v_color;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
	//gl_Position = pos;
	v_color = color;
}