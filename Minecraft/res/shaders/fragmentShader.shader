#version 330 core

out vec4 fragColor;

//in vec4 v_color;

in vec2 vTexCoord;

uniform sampler2D u_Texture;

void main()
{
	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	vec4 texColor = texture(u_Texture, vTexCoord);
	fragColor = texColor;
	//color = v_color;
}