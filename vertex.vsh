#version 120

// Input vertex data
attribute vec3 vPosition;
attribute vec3 vertexColor;

// Output data
varying vec3 fragmentColor;

// Uniform vertex data (values that stay constant for the whole mesh)
uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vPosition, 1);
    fragmentColor = vertexColor;
}
