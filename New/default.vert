#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 u_position;
uniform float u_scale;

void main()
{
    vec2 scaled = aPos * u_scale;
    gl_Position = vec4(scaled + u_position, 0.0, 1.0);
}