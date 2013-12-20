#version 330 core

// Input vertex data
//attribute vec3 vPosition;
//attribute vec3 vertexColor;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vertexColor;

// Output data
//varying vec3 fragmentColor;
out vec3 fragmentColor;

// Uniform vertex data (values that stay constant for the whole mesh)
uniform mat4 MVP;
uniform vec3 move;

void main() {
    gl_Position = MVP * (vec4(vPosition, 1) * 0.1);
    fragmentColor = vertexColor;
}
